def generate_rsa_keys(bit_size):
    """
    Generate RSA keys: n, e, p, q, d (probably prime)
    """
    lower_bound = 2 ** (bit_size // 2 - 1)
    upper_bound = 2 ** (bit_size // 2) - 1

    while True:
        # Generate two distinct primes p and q
        p = random_prime(upper_bound, False, lbound=lower_bound)
        q = random_prime(upper_bound, False, lbound=lower_bound)
        while p == q:  # Ensure p and q are distinct
            q = random_prime(upper_bound, False, lbound=lower_bound)

        n = p * q
        phi = (p - 1) * (q - 1)
        e = 65537
        
        try:
            d = inverse_mod(e, phi)  # Try to find the modular inverse
            break  # If successful, break the loop and return keys
        except ZeroDivisionError:
            # If inverse_mod fails, retry with new p and q
            print(f"Retrying key generation because inverse_mod failed for e={e} and phi={phi}")
            continue
    
    return n, e, p, q, d

def save_rsa_keys_to_txt(keys, filename):
    """
    Save multiple RSA keys to a .txt file without 'Key X' headers.
    """
    with open(filename, "w") as file:
        for n, e, p, q, d in keys:
            file.write(f"n = 0x{n:x}\n")
            file.write(f"e = 0x{e:x}\n")
            file.write(f"p = 0x{p:x}\n")
            file.write(f"q = 0x{q:x}\n")
            file.write(f"d = 0x{d:x}\n")

def generate_and_save_keys():
    """
    Generate and save RSA keys for 1024, 2048, and 15360 bits
    """
    key_sizes = [1024, 2048, 15360]
    for bit_size in key_sizes:
        keys = []
        print(f"Generating {bit_size}-bit RSA keys...")
        for i in range(10):  # Generate 10 keys
            print(f"  Generating key {i + 1}/10 for {bit_size}-bit...")
            keys.append(generate_rsa_keys(bit_size))
        print(f"    Key {i + 1}/10 generated successfully.")
        filename = f"rsa_{bit_size}_params.txt"
        save_rsa_keys_to_txt(keys, filename)
        print(f"Saved {bit_size}-bit RSA keys to {filename}\n")

# Run the key generation and saving
generate_and_save_keys()