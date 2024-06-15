import random
import string

def binary_little_endian_to_hex_little_endian(binary_str):
    # Pad binary_str to be a multiple of 8 bits
    padded_binary_str = binary_str.ljust((len(binary_str) + 7) // 8 * 8, '0')

    # Split the binary string into bytes (8 bits)
    bytes_list = [padded_binary_str[i:i+8] for i in range(0, len(padded_binary_str), 8)]

    # Reverse the order of the bytes to convert from little-endian to big-endian
    bytes_list.reverse()

    # Join the bytes back into a single string
    big_endian_binary_str = ''.join(bytes_list)

    # Convert the big-endian binary string to an integer
    integer_value = int(big_endian_binary_str, 2)

    # Convert the integer to a big-endian hexadecimal string
    hex_str = format(integer_value, 'x')

    # Pad hex_str to be a multiple of 2 characters (1 byte)
    padded_hex_str = hex_str.zfill((len(hex_str) + 1) // 2 * 2)

    # Split the hexadecimal string into bytes (2 characters)
    hex_bytes_list = [padded_hex_str[i:i+2] for i in range(0, len(padded_hex_str), 2)]

    # Reverse the order of the bytes to convert from big-endian to little-endian
    hex_bytes_list.reverse()

    # Join the bytes back into a single string
    little_endian_hex_str = ''.join(hex_bytes_list)

    return little_endian_hex_str



def generate_random_string(length):
    letters = string.ascii_letters  # This includes both uppercase and lowercase letters
    result_str = ''.join(random.choice(letters) for i in range(length))
    return result_str

def draw(i, j, colorinbinare):
    # Ensure colorinbinare is a 4-bit binary string
    colorinbinare = format(int(colorinbinare, 2), '04b')
    
    # Ensure j is a 6-bit binary string
    j_binary = format(j, '06b')
    
    # Ensure i is a 6-bit binary string
    i_binary = format(i, '06b')
    
    # Concatenate the binary strings to get the desired format
    b =   i_binary + j_binary + colorinbinare
    
    r = generate_random_string(10)

    code = f"""
BIN @{r}
@{r} 0x{binary_little_endian_to_hex_little_endian(b)}
ADD
OUT"""
    print(code)


print("LDC 0")
## be9iyat lehlel
draw(37, 24, '1001')
draw(37, 25, '1001')
draw(38, 26, '1001')
draw(38, 27, '1001')
draw(38, 25, '1001')
draw(37, 40, '1001')
draw(37, 39, '1001')
draw(38, 39, '1001')
draw(38, 38, '1001')
draw(38, 37, '1001')

## nejma
draw(32, 32, '1001')
draw(32, 31, '1001')
draw(31, 32, '1001')
draw(32, 33, '1001')
draw(33, 32, '1001')
draw(31, 31, '1001')
draw(31, 33, '1001')
draw(33, 33, '1001')
draw(33, 31, '1001')
draw(30, 32, '1001')
draw(29, 32, '1001')
draw(32, 30, '1001')
draw(32, 29, '1001')
draw(32, 34, '1001')
draw(32, 35, '1001')
draw(34, 31, '1001')
draw(34, 32, '1001')
draw(34, 33, '1001')
draw(34, 30, '1001')
draw(35, 30, '1001')
draw(35, 31, '1001')
draw(34, 34, '1001')
draw(35, 34, '1001')
draw(35, 33, '1001')