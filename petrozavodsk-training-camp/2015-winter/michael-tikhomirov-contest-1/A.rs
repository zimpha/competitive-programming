use std::{
    cmp::min,
    io::{self, Write},
    str,
};

struct Scanner<R> {
    reader: R,
    buf_str: Vec<u8>,
    buf_iter: str::SplitAsciiWhitespace<'static>,
}

impl<R: io::BufRead> Scanner<R> {
    fn new(reader: R) -> Self {
        Self {
            reader,
            buf_str: Vec::new(),
            buf_iter: "".split_ascii_whitespace(),
        }
    }
    fn next<T: str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buf_iter.next() {
                return token.parse().ok().expect("Failed parse");
            }
            self.buf_str.clear();
            self.reader.read_until(b'\n', &mut self.buf_str).expect("Failed read");
            self.buf_iter = unsafe {
                let slice = str::from_utf8_unchecked(&self.buf_str);
                std::mem::transmute(slice.split_ascii_whitespace())
            }
        }
    }
}

fn main() {
    let (stdin, stdout) = (io::stdin(), io::stdout());
    let mut cin = Scanner::new(stdin.lock());
    let mut cout = io::BufWriter::new(stdout.lock());

    let n: usize = cin.next();
    let m: usize = cin.next();
    let mut h: Vec<i64> = (0..n).map(|_| cin.next()).collect();

    for i in (1..n).rev() {
        h[i] -= h[i - 1];
    }
    h[0] = primal_dual::INF;
    h.push(primal_dual::INF);

    let mut g = vec![vec![primal_dual::INF; n + 1]; n + 1];
    for _ in 0..m {
        let op: char = cin.next();
        let len: usize = cin.next();
        let cost: i64 = cin.next();
        for i in 0..n - len + 1 {
            if op == '-' {
                g[i][i + len] = min(g[i][i + len], cost);
            } else {
                g[i + len][i] = min(g[i + len][i], cost);
            }
        }
    }

    // floyd
    for i in 0..n + 1 {
        g[i][i] = 0;
    }
    for k in 0..n + 1 {
        for i in 0..n + 1 {
            for j in 0..n + 1 {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }

    let mut pos = Vec::new();
    let mut neg = Vec::new();
    let mut total = 0;

    for i in 0..n + 1 {
        if h[i] > 0 {
            pos.push(i);
        }
        if h[i] < 0 {
            neg.push(i);
            total -= h[i];
        }
    }

    let n = pos.len();
    let m = neg.len();
    let src = n + m;
    let tar = n + m + 1;

    let mut min_cost = primal_dual::MinCostFlow::new(n + m + 2);

    for i in 0..n {
        min_cost.add_edge(src, i, h[pos[i]], 0);
    }

    for i in 0..m {
        min_cost.add_edge(i + n, tar, -h[neg[i]], 0);
    }

    for i in 0..n {
        for j in 0..m {
            if g[pos[i]][neg[j]] != primal_dual::INF {
                min_cost.add_edge(i, j + n, primal_dual::INF, g[pos[i]][neg[j]]);
            }
        }
    }

    let (max_flow, min_cost) = min_cost.solve(src, tar);

    if max_flow == total {
        writeln!(cout, "{}", min_cost).ok();
    } else {
        writeln!(cout, "-1").ok();
    }
}

mod primal_dual {
    use std::{cmp::min, collections::BinaryHeap, i64};

    pub const INF: i64 = 1_000_000_000_000_000;

    #[derive(Default, Clone)]
    struct Edge {
        to: usize,
        capacity: i64,
        cost: i64,
        rev: usize,
        is_rev: bool,
    }

    pub struct MinCostFlow {
        edges: Vec<Vec<Edge>>,
        phi: Vec<i64>,
        dist: Vec<i64>,
        mark: Vec<bool>,
        n: usize,
    }

    impl MinCostFlow {
        pub fn new(n: usize) -> Self {
            Self {
                edges: vec![Default::default(); n],
                phi: vec![0; n],
                dist: vec![0; n],
                mark: vec![false; n],
                n,
            }
        }

        pub fn add_edge(&mut self, from: usize, to: usize, capacity: i64, cost: i64) {
            let rev_from = self.edges[to].len();
            let rev_to = self.edges[from].len();
            self.edges[from].push(Edge {
                to,
                capacity,
                cost,
                rev: rev_from,
                is_rev: false,
            });
            self.edges[to].push(Edge {
                to: from,
                capacity: 0,
                cost: -cost,
                rev: rev_to,
                is_rev: true,
            });
        }

        pub fn solve(&mut self, src: usize, tar: usize) -> (i64, i64) {
            // change to SPFA if negtive edges exist
            self.dijkstra(tar);

            let mut max_flow = 0;
            let mut min_cost = 0;

            loop {
                loop {
                    self.mark = vec![false; self.mark.len()];
                    let flow = self.augment(src, i64::MAX, tar);
                    max_flow += flow;
                    min_cost += flow * self.phi[src];
                    if flow == 0 {
                        break;
                    }
                }
                if !self.modify_phi(tar) {
                    break;
                }
            }

            (max_flow, min_cost)
        }

        fn augment(&mut self, u: usize, limit: i64, tar: usize) -> i64 {
            if u == tar {
                return limit;
            }

            self.mark[u] = true;
            let mut cur_flow = limit;

            for i in 0..self.edges[u].len() {
                let capacity = self.edges[u][i].capacity;
                if capacity <= 0 {
                    continue;
                }
                let to = self.edges[u][i].to;
                let cost = self.edges[u][i].cost;
                if !self.mark[to] && self.phi[to] + cost == self.phi[u] {
                    let now = self.augment(to, min(capacity, cur_flow), tar);
                    cur_flow -= now;
                    self.edges[u][i].capacity -= now;
                    let rev = self.edges[u][i].rev;
                    self.edges[to][rev].capacity += now;
                    if cur_flow == 0 {
                        self.mark[u] = false;
                        return limit;
                    }
                }
            }

            limit - cur_flow
        }

        fn modify_phi(&mut self, tar: usize) -> bool {
            let mut pq = BinaryHeap::new();
            for i in 0..self.n {
                if self.mark[i] {
                    self.dist[i] = 0;
                    pq.push((0, i));
                } else {
                    self.dist[i] = INF;
                }
            }

            while let Some((d, u)) = pq.pop() {
                if u == tar {
                    break;
                }
                if self.dist[u] < d {
                    continue;
                }
                for e in &self.edges[u] {
                    if e.capacity > 0 && -d + e.cost + self.phi[e.to] - self.phi[u] < self.dist[e.to] {
                        self.dist[e.to] = -d + e.cost + self.phi[e.to] - self.phi[u];
                        pq.push((-self.dist[e.to], e.to));
                    }
                }
            }

            if self.dist[tar] == INF {
                return false;
            }
            for i in 0..self.n {
                if self.dist[i] < self.dist[tar] {
                    self.phi[i] += self.dist[tar] - self.dist[i];
                }
            }
            true
        }

        fn dijkstra(&mut self, tar: usize) {
            let mut pq = BinaryHeap::new();
            for i in 0..self.n {
                self.phi[i] = INF;
            }
            self.phi[tar] = 0;
            pq.push((0, tar));
            while let Some((d, u)) = pq.pop() {
                if self.phi[u] < d {
                    continue;
                }
                for e in &self.edges[u] {
                    if self.edges[e.to][e.rev].capacity > 0 && self.edges[e.to][e.rev].cost - d < self.phi[e.to] {
                        self.phi[e.to] = self.edges[e.to][e.rev].cost - d;
                        pq.push((-self.phi[e.to], e.to));
                    }
                }
            }
        }
    }
}
