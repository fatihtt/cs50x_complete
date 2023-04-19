# TODO
from cs50 import get_int

height = -1

# take the height

while height > 8 or height < 1:
    height = get_int("what is height? ( 1 to 8 ) ")

# print(f"Height you wish is {height}")

# write each row in a row

for x in range(height):
    y = x + 1
    space_count = height - y
    print(' ' * space_count + '#' * y + '  ' + '#' * y)