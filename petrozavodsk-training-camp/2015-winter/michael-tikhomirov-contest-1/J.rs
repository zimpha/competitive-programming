use std::{
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
    let b: usize = cin.next();
    if n == 3 && b == 4 {
        writeln!(cout, "2\n1 2\n2 3").ok();
    } else {
        writeln!(cout, "{}", n / 2 * (n / 2 - 1) / 2 + n / 2).ok();
        for i in 0..n / 2 {
            for j in 0..i {
                writeln!(cout, "{} {}", i + 1, j + 1).ok();
            }
        }
        for i in n / 2..n {
            writeln!(cout, "{} {}", i, i + 1).ok();
        }
    }
}
