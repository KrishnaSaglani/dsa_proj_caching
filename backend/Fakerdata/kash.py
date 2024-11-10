from faker import Faker
import random

# Initialize Faker and set the number of operations
faker = Faker()
num_operations = 1  # Total number of operations (get and put combined)
max_key_value = 200   # Maximum range for key values

# File to write the data
output_file = "lru_cache_operations.txt"

with open(output_file, "w") as file:
    for _ in range(num_operations):
        operation_type = random.choice(["get", "put"])
        
        if operation_type == "put":
            key = random.randint(1, max_key_value)
            value = faker.name()  # Generating random names as values
            file.write(f"put {key} {value}\n")
        
        else:  # "get" operation
            key = random.randint(1, max_key_value)
            file.write(f"get {key}\n")

print(f"Data generated and written to {output_file}")
