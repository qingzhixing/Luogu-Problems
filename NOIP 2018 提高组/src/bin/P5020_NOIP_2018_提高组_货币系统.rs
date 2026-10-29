use std::io::{self, Read};
use std::str::{FromStr, SplitAsciiWhitespace};
use std::vec;

const _MAX_N: usize = 110;
const MAX_M: usize = 3e5 as usize;

fn next<T: FromStr>(tokens: &mut SplitAsciiWhitespace) -> T {
    tokens.next().unwrap().parse().ok().unwrap()
}

#[allow(dead_code)]
fn next_str(tokens: &mut SplitAsciiWhitespace) -> Vec<char> {
    tokens.next().unwrap().chars().collect()
}

fn solution(tokens: &mut SplitAsciiWhitespace) {
    let n: usize = next(tokens);
    let mut a: Vec<usize> = (0..n).map(|_| next(tokens)).collect();
    a.sort_unstable();

    let mut selected = Vec::<usize>::new();
    // dp[i] 表示值为 i 的数字可以被已选数字表示出来
    let mut dp = vec![false; MAX_M];
    dp[0] = true;

    // 判断 a 中数字能否被选中
    for num in a {
        // 已能被表示，跳过
        if dp[num] {
            continue;
        }

        selected.push(num);

        // 状态转移
        // 用当前数字筛后面的数字
        for nxt in num..MAX_M {
            if dp[nxt - num] {
                dp[nxt] = true;
            }
        }
    }

    println!("{}", selected.len());
}

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut tokens = input.split_ascii_whitespace();

    let t: usize = next(&mut tokens);
    for _ in 0..t {
        solution(&mut tokens);
    }
}
