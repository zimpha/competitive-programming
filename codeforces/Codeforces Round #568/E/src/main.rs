use std::io::{self, Write};
use std::str;
use std::num;

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

    let cases = cin.next::<u32>();
    for _ in 0..cases {
        let n = cin.next::<u32>();
        let m = cin.next::<u32>();
        let mut snakes = Vec::new();
        for _ in 0..26 {
            snakes.push(Vec::new());
        }
        for i in 0..n {
            let ss = cin.next_line();
            let s = ss.as_bytes();
            for j in 0..m {
                if s[j as usize] != '.' as u8 {
                    snakes[s[j as usize] as usize - 'a' as usize].push((i as i32, j as i32));
                }
            }
        }
        let mut valid = true;
        for i in 0..26 {
            valid = valid & valid_snake(&snakes[i as usize]);
        }
    }
}

fn full_snake(snake: &Vec<(i32, i32)>) -> bool {
    if snake.len() <= 1 {
        return true
    }
    let a = snake[0];
    let b = snake.last().unwrap();

    snake.len() as i32 == (b.1 - a.1).abs() + (b.0 - a.0).abs() + 1
}

fn valid_snake(snake: &Vec<(i32, i32)>) -> bool {
    if snake.len() <= 1 {
        return true;
    }
    let a = snake[0];
    let b = snake[1];

    if !(a.0 == b.0 || a.1 == b.1) {
        return false;
    }
    for e in snake {
        if e.0 == a.0 && e.1 == a.1 {
            continue;
        }
        if e.0 == b.0 && e.1 == b.1 {
            continue;
        }
        if a.0 == e.0 && (e.1 - a.1) * (e.1 - b.1) > 0 {
            return false;
        }
        if a.1 == e.1 && (e.0 - a.0) * (e.0 - b.0) > 0 {
            return false;
        }
    }

    true
}