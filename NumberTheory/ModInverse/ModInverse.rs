fn gcd(a: i64, b: i64) -> (i64, i64, i64) {
    if b != 0 {
        let (g, x, y) = gcd(b, a % b);
        (g, y, x - a / b * y)
    } else if a >= 0 {
        (a, 1, 0)
    } else {
        (-a, -1, 0)
    }
}

fn lcm(a: i64, b: i64) -> i64 {
    a / gcd(a, b).0 * b
}
