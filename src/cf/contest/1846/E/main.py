def power(base, exponent):
    result = 1
    while exponent > 0:
        if exponent % 2 == 1:
            result *= base
        base *= base
        exponent //= 2
    return result

tt = int(input())
for _ in range(tt):
    n = int(input())
    ok = False
    for p in range(2, 64):
        l, r = 2, int(n ** (1 / p)) + 1
        while l <= r:
            m = (l + r) // 2
            v = power(m, p + 1) - 1
            nz = n * (m - 1)
            if v < nz:
                l = m + 1
            if v > nz:
                r = m - 1
            if abs(v - nz) <= 0.1:
                ok = True
                break
    print("YES" if ok else "NO")

