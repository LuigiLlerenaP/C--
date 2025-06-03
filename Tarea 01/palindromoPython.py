# Función para pedir al usuario una cadena de texto
def ask_for_input():
    input_str = input("Enter a string: ")  # Asignar el valor de entrada a la variable input_str
    return input_str

# Función para comprobar si una palabra es un palíndromo
def is_palindrome(letter):
    length_middle_letter = len(letter) // 2
    last_position = len(letter) - 1
    for i in range(length_middle_letter):
        if letter[i].lower() != letter[last_position].lower():
            return False
        last_position -= 1
    return True

# Función principal
def main():
    input_user = ask_for_input()
    palindrome = "is a palindrome" if is_palindrome(input_user) else "is not a palindrome"
    print(f"The string {input_user} {palindrome}")

if __name__ == "__main__":
    main()
