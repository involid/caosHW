import sys

sys.path += ["/eq/ewqwe/wqe/qw/e/qwe/qw/e"]


class colors:
    GREEN = '\033[1;32m'
    RED = '\033[1;31m'
    ENDC = '\033[0m'


import primes

test_arguments = [100, 17, 1505112, 2, 67, 75]
test_answers = [
    [1, 2, 2, 5, 5],
    "Prime!",
    [1, 2, 2, 2, 3, 7, 17, 17, 31],
    "Prime!",
    "Prime!",
    [1, 3, 5, 5]
]

for i in range(len(test_arguments)):
    print("===== Test " + str(i+1) + " =====")
    print("Expected output:")
    print(test_answers[i])
    print("Real output:")
    real_answer = primes.factor_out(test_arguments[i])
    print(real_answer)

    if (real_answer == test_answers[i]):
        print(colors.GREEN + "Test is passed" + colors.ENDC)
    else:
        print(colors.RED + "Test is failed" + colors.ENDC)

    if (i+1 != len(test_arguments)):
        print()
