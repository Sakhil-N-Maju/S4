while true; do  # Infinite loop to keep showing the menu
    echo "ENTER THE CHOICE"
    echo "1. Add"
    echo "2. Subtract"
    echo "3. Multiply"
    echo "4. Divide"
    echo "5. Exit"
    
    read c  # Read the user's choice
    
    if [ "$c" -eq 5 ]; then
        echo "Exiting..."
        break  # Exit the loop and terminate the script
    fi
    
    echo "ENTER THE NUMBERS"
    read num1 num2  # Read two numbers
    
    # Check if the inputs are valid integers
    if ! [[ "$num1" =~ ^-?[0-9]+$ ]] || ! [[ "$num2" =~ ^-?[0-9]+$ ]]; then
        echo "Invalid input! Please enter valid integers."
        continue  # Skip to the next iteration of the loop
    fi
    
    # Perform the chosen operation
    case $c in
    1)
        result=$(($num1 + $num2))
        echo "Result: $num1 + $num2 = $result"
        ;;
    2)
        result=$(($num1 - $num2))
        echo "Result: $num1 - $num2 = $result"
        ;;
    3)
        result=$(($num1 * $num2))
        echo "Result: $num1 * $num2 = $result"
        ;;
    4)
        if [ $num2 -ne 0 ]; then
            result=$(($num1 / $num2))
            echo "Result: $num1 / $num2 = $result"
        else
            echo "Division by zero not possible"
        fi
        ;;
    *)
        echo "Invalid choice"
        ;;
    esac
    
    echo "------------------------------------"  # To separate the operations visually
done
