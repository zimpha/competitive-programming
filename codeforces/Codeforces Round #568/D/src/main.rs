use std::io::{self, Write};
use std::str;
use std::collections::HashMap;

struct Scanner<R> {
    reader: R,
    buf_str: Vec<u8>,
    buf_iter: str::SplitAsciiWhitespace<'static>
}

#[allow(dead_code)]
impl<R: io::BufRead> Scanner<R> {
    fn new(reader: R) -> Self {
        Self { reader, buf_str: Vec::new(), buf_iter: "".split_ascii_whitespace() }
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

    fn next_line(&mut self) -> String {
        let mut line = String::new();
        self.reader.read_line(&mut line).expect("Failed to read line");
        line
    }

    fn next_vec<T: str::FromStr>(&mut self) -> Vec<T> {
        let mut res: Vec<T> = Vec::new();
        loop {
            loop {
                match self.buf_iter.next() {
                    Some(token) => res.push(token.parse().ok().expect("Failed parse")),
                    None => break,
                }
            }
            if res.len() > 0 {
                return res;
            }
            self.buf_str.clear();
            self.reader.read_until(b'\n', &mut self.buf_str).expect("Failed read");
            self.buf_iter = unsafe {
                let slice = str::from_utf8_unchecked(&self.buf_str);
                std::mem::transmute(slice.split_ascii_whitespace())
            }
        }
    }

    fn next_vec_n<T: str::FromStr>(&mut self, n: u32) -> Vec<T> {
        (0..n).map(|_| self.next()).collect()
    }
}

fn main() {
    let (stdin, stdout) = (io::stdin(), io::stdout());
    let mut cin = Scanner::new(stdin.lock());
    let mut cout = io::BufWriter::new(stdout.lock());

    let n = cin.next::<u32>();
    let mut a = cin.next_vec_n::<i32>(n);

    let mut diff_p = Vec::with_capacity(n as usize);
    let mut diff_s = Vec::with_capacity(n as usize);
    let mut map = HashMap::new();

    for i in 0..n {
        map.insert(a[i as usize], i + 1);
    }

    a.sort();

    for i in 0..n {
        if i == 0 {
            diff_p.push(0);
        } else if i == 1 {
            diff_p.push(a[i as usize] - a[i as usize - 1]);
        } else {
            let diff = a[i as usize] - a[i as usize - 1];
            if diff == *diff_p.last().unwrap() {
                diff_p.push(diff);
            } else {
                diff_p.push(-1);
            }
        }
    }

    a.reverse();

    for i in 0..n {
        if i == 0 {
            diff_s.push(0);
        } else if i == 1 {
            diff_s.push(a[i as usize - 1] - a[i as usize]);
        } else {
            let diff = a[i as usize - 1] - a[i as usize];
            if diff == *diff_s.last().unwrap() {
                diff_s.push(diff);
            } else {
                diff_s.push(-1);
            }
        }
    }

    diff_s.reverse();

    if n == 2 {
        writeln!(cout, "1").ok();
        return;
    }

    a.reverse();

    //writeln!(cout, "{:?}", a);
    //writeln!(cout, "{:?}", diff_p);
    //writeln!(cout, "{:?}", diff_s);

    for i in 0..n {
        let x = if i == 0 { a[i as usize + 1] } else { a[0] };
        let y = if i == n - 1 { a[i as usize - 1] } else { a[n as usize - 1] };
        if (y - x) % (n - 2) as i32 != 0 {
            continue;
        }
        let d = (y - x) / (n - 2) as i32;

        let mut valid = true;

        if i > 1 {
            valid = valid && d == diff_p[i as usize - 1];
        }
        if i < n - 2 {
            valid = valid && d == diff_s[i as usize + 1];
        }
        if i != 0 && i != n - 1 {
            valid = valid && d == a[i as usize + 1] - a[i as usize - 1];
        }
        if valid {
            writeln!(cout, "{}", map.get(&a[i as usize]).unwrap()).ok();
            return;
        }
    }
    writeln!(cout, "-1").ok();
}