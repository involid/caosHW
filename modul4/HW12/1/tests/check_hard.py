import sys

sys.path += ["/eq/ewqwe/wqe/qw/e/qwe/qw/e"]


import primes

print("===== Test 1 =====")
print("Expected output:")
print([1, 2, 2, 5, 5])
print("Real output:")
print(primes.factor_out(-100))
print()

print("===== Test 2 =====")
print("Expected output:")
print("Prime!")
print("Real output:")
print(primes.factor_out(-17))
print()

print("===== Test 3 =====")
print("Expected output:")
print([1])
print("Real output:")
print(primes.factor_out(1))
print()

print("===== Test 4 =====")
print("Expected output:")
print([1])
print("Real output:")
print(primes.factor_out(-1))
print()

print("===== Test 5 =====")
print("Expected output:")
print("ValueError('<Some text>')")
print("Real output:")
try:
    print(primes.factor_out(0))
except Exception as e:
    print(repr(e))
print()

print("===== Test 6 =====")
print("Expected output:")
print("ValueError('<Some text>')")
print("Real output:")
try:
    print(primes.factor_out(123456789123456789123456789))
except Exception as e:
    print(repr(e))
print()

print("===== Test 7 =====")
print("Expected output:")
print("ValueError('<Some text>')")
print("Real output:")
try:
    print(primes.factor_out(-123456789123456789123456789))
except Exception as e:
    print(repr(e))
print()

print("===== Test 8 =====")
print("Expected output:")
print("TypeError('<Some text>')")
print("Real output:")
try:
    print(primes.factor_out("abc"))
except Exception as e:
    print(repr(e))
print()

print("===== Test 9 =====")
print("Expected output:")
print("TypeError('function takes exactly 1 argument (2 given)')")
print("Real output:")
try:
    print(primes.factor_out(10, 20))
except Exception as e:
    print(repr(e))
