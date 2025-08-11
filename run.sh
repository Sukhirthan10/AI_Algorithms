#!/bin/bash

# Define colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# --- List of your 15 C++ files ---
files=(
    "A_star.cpp"
    "bfs.cpp"
    "bfs_history.cpp"
    "beam_search.cpp"
    "beam_search_history.cpp"
    "bms.cpp"
    "branch_bound.cpp"
    "branch_bound_history.cpp"
    "branch_bound_heuristics.cpp"
    "dfs.cpp"
    "dfs_history.cpp"
    "hill_climb.cpp"
    "hill_climb_history.cpp"
    "bfs+dfs.cpp" # This is your IDDFS implementation
    "oracle.cpp"
)


show_menu() {
    clear
    echo -e "${BLUE}===========================================${NC}"
    echo -e "${BLUE}   AI Search Algorithm Runner Menu         ${NC}"
    echo -e "${BLUE}===========================================${NC}"
    
    for i in "${!files[@]}"; do
        filename="${files[$i]}"
        warning=""
        
        printf "  %2d) %-35s %s\n" "$((i+1))" "$filename" "$warning"
    done
    
    echo "-------------------------------------------"
    echo -e "   0) ${RED}Exit${NC}"
    echo -e "${BLUE}===========================================${NC}"
}

while true; do
    show_menu
    read -p "Enter your choice [0-$((${#files[@]}))]: " choice

    if [[ "$choice" -eq 0 ]]; then
        echo -e "\n${RED}Exiting program.${NC}"
        break
    fi

    if ! [[ "$choice" =~ ^[0-9]+$ ]] || [[ "$choice" -lt 1 ]] || [[ "$choice" -gt "${#files[@]}" ]]; then
        echo -e "\n${RED}Invalid choice. Please try again.${NC}"
        read -p "Press Enter to continue..."
        continue
    fi

    selected_file="${files[$((choice-1))]}"
    output_name="${selected_file%.cpp}"

    echo -e "\n${GREEN}--- Compiling: $selected_file ---${NC}"
    
    if g++ -std=c++17 "$selected_file" -o "$output_name"; then
        echo -e "${GREEN}Compilation successful.${NC}"
        echo -e "\n${GREEN}--- Running: ./$output_name ---${NC}"
        
        ./"$output_name"
        
        echo -e "${GREEN}Execution finished.${NC}"
    else
        echo -e "\n${RED}--- Compilation Failed ---${NC}"
        echo -e "${RED}There was an error compiling $selected_file.${NC}"
    fi

    read -p "Press Enter to return to the menu..."
done