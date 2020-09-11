use std::{
  io::{self, Write},
  mem, str,
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
  let mut a = vec![vec![0; n + 1]; n];
  let mut edges = vec![vec![]; n];
  for _ in 0..m {
      let x: usize = cin.next();
      let y: usize = cin.next();
      edges[x - 1].push(y - 1);
      edges[y - 1].push(x - 1);
  }

  for i in 0..n {
      for j in &edges[i] {
          a[i][*j] = 1;
      }
      if edges[i].len() % 2 == 1 {
          a[i][i] = 1;
          a[i][n] = 1;
      }
  }
  //println!("{:?}", a);

  if let Some(ret) = gauss(&mut a) {
      let s: String = ret.iter().map(|&x| if x == 0 { 'A' } else { 'B' }).collect();
      writeln!(cout, "{}", s).ok();
  } else {
      writeln!(cout, "IMPOSSIBLE").ok();
  }
}

fn gauss(a: &mut Vec<Vec<u32>>) -> Option<Vec<u32>> {
  let n = a.len();
  for i in 0..n {
      let mut s = i;
      while s < n && a[s][i] == 0 {
          s += 1;
      }
      if s == n {
          continue;
      }
      if s != i {
          let x = mem::replace(&mut a[s], vec![]);
          let y = mem::replace(&mut a[i], vec![]);
          mem::replace(&mut a[s], y);
          mem::replace(&mut a[i], x);
      }
      for j in 0..n {
          if i == j {
              continue;
          }
          if a[j][i] == 1 {
              for k in 0..n + 1 {
                  a[j][k] ^= a[i][k];
              }
          }
      }
  }
  let mut ret = vec![0; n];
  for i in 0..n {
      if a[i][i] == 0 && a[i][n] == 1 {
          return None;
      }
      ret[i] = a[i][n];
  }
  Some(ret)
}
