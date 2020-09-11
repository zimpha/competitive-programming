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

const MOD: u64 = 1_000_000_000 + 7;

fn main() {
  let (stdin, stdout) = (io::stdin(), io::stdout());
  let mut cin = Scanner::new(stdin.lock());
  let mut cout = io::BufWriter::new(stdout.lock());

  let n: usize = cin.next();

  let mut inv = vec![1; n + 1];
  for i in 2..n + 1 {
    inv[i] = (MOD - MOD / i as u64) * inv[(MOD % i as u64) as usize] % MOD;
  }

  let mut g = 1;
  let mut sf = 1;
  let mut f = 1;
  for i in 1..n + 1 {
    f = (2 * sf * inv[i] + 2 * g * inv[i] % MOD * inv[i]) % MOD;
    g = (f + (1 + 4 * inv[i]) * g) % MOD;
    sf = (sf + f) % MOD;
  }
  writeln!(cout, "{}", (f - (n as u64 + 1) * (n as u64 + 1) % MOD + MOD) % MOD).ok();
}