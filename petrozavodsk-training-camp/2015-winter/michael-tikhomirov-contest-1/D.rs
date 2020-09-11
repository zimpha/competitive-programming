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
    let mut sol = Solution::default();
    sol.run();
}

const NULL_INDEX: usize = !0;

#[derive(Default)]
struct Solution {
    occ: Vec<bool>,
    static_root: Vec<usize>,
    dynamic_root: Vec<usize>,
    root: Vec<usize>,
}

impl Solution {
    fn init(&mut self, n: usize) {
        self.occ.resize_with(n, Default::default);
        self.static_root.resize_with(n, Default::default);
        self.dynamic_root.resize_with(n, Default::default);
        self.root.resize_with(n, Default::default);
    }

    fn get_static_root(&mut self, x: usize) -> usize {
        if self.occ[x] || self.root[x] == NULL_INDEX {
            return x;
        }
        if self.static_root[x] == NULL_INDEX {
            self.static_root[x] = self.get_static_root(self.root[x]);
        }
        self.static_root[x]
    }

    fn get_dynamic_root(&mut self, mut x: usize) -> usize {
        x = self.get_static_root(x);
        if self.root[x] == NULL_INDEX {
            return x;
        }
        if self.dynamic_root[x] == NULL_INDEX {
            self.dynamic_root[x] = self.get_dynamic_root(self.root[x]);
        }
        self.dynamic_root[x]
    }

    pub fn run(&mut self) {
        let (stdin, stdout) = (io::stdin(), io::stdout());
        let mut cin = Scanner::new(stdin.lock());
        let mut cout = io::BufWriter::new(stdout.lock());

        let n: usize = cin.next();
        self.init(n);

        let q: usize = cin.next();

        let mut a: Vec<i32> = vec![0; n];
        for i in 0..n {
            a[i] = cin.next();
            self.root[i] = NULL_INDEX;
        }

        let sq = (q as f64).sqrt() as usize;
        let mut modified = Vec::new();
        let mut prefix_sum = vec![0; n + 1];
        let mut subtree = vec![vec![]; n];
        for block in (0..q).step_by(sq) {
            let nq = min(sq, q - block);
            let mut ops = Vec::with_capacity(nq);
            for i in 0..n {
                self.occ[i] = false;
                self.static_root[i] = NULL_INDEX;
            }
            for _ in 0..nq {
                let op: String = cin.next();
                let x: usize = cin.next();
                let y: i32 = cin.next();
                if op == "set" {
                    self.occ[x - 1] = true;
                } else if op == "link" {
                    self.occ[x - 1] = true;
                }
                ops.push((op, x, y));
            }
            modified.clear();
            for i in 0..n {
                if self.occ[i] {
                    modified.push(i);
                    subtree[i].clear();
                }
            }
            for i in 0..n {
                let r = self.get_static_root(i);
                prefix_sum[i + 1] = if self.occ[r] {
                    subtree[r].push(i);
                    0
                } else {
                    a[r]
                };
                prefix_sum[i + 1] += prefix_sum[i];
            }
            for (op, x, y) in ops {
                if op == "set" {
                    self.root[x - 1] = NULL_INDEX;
                    a[x - 1] = y;
                } else if op == "link" {
                    self.root[x - 1] = y as usize - 1;
                    a[x - 1] = 0;
                } else {
                    for &i in &modified {
                        self.dynamic_root[i] = NULL_INDEX;
                    }
                    let mut ret = prefix_sum[y as usize] - prefix_sum[x - 1];
                    for &i in &modified {
                        let r = self.get_dynamic_root(i);
                        // [x - 1, y - 1]
                        let cnt = subtree[i].binary_search(&(y as usize)).unwrap_or_else(|x| x)
                            - subtree[i].binary_search(&(x - 1)).unwrap_or_else(|x| x);
                        ret += a[r] * cnt as i32;
                    }
                    writeln!(cout, "{}", ret).ok();
                }
            }
        }
    }
}
