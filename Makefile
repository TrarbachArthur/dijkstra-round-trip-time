EXECUTABLE       = trab2
SRC              = ./src
INCLUDE          = ./include
OBJ              = ./obj
FLAGS            = -lm -pedantic -Wall -g
ADD_FLAGS        = -Wextra
COMPILER         = gcc   

# Path and extesions
C_FILES        = $(wildcard $(SRC)/*.c | $(SRC)/**/*.c)
OBJ_PATH_FILES = $(patsubst $(SRC)%,$(OBJ)%,$(C_FILES))
OBJ_FILES      = $(patsubst %.c,%.o,$(OBJ_PATH_FILES))

#===========================================================#
# Main target
all: clean create_dir $(OBJ_FILES) $(EXECUTABLE)

# Creatig objects directory
create_dir: 
	@ mkdir $(OBJ)

# Compiling cpp files
$(OBJ)/%.o: $(SRC)/%.c 
	@ $(COMPILER) -c $< -o $@

# Creating executable
$(EXECUTABLE): 
	@ $(COMPILER) $< $(OBJ)/*.o -o $@ $(FLAGS)

# Cleaning workspace
clean:
	@ rm -rf $(OBJ) $(EXECUTABLE) *.txt

run:
	@ ./trab2 test/in/N10_S3_C3_M3.txt out1.txt
	@ ./trab2 test/in/N100_S20_C30_M5.txt out2.txt
	@ ./trab2 test/in/N1000_S50_C300_M10.txt out3.txt
	@ ./trab2 test/in/N10000_S50_C300_M10.txt out4.txt

diff:
	@ diff out1.txt test/out/N10_S3_C3_M3-solution.txt
	@ diff out2.txt test/out/N100_S20_C30_M5-solution.txt
	@ diff out3.txt test/out/N1000_S50_C300_M10-solution.txt
	@ diff out4.txt test/out/N10000_S50_C300_M10-solution.txt

valgrind1:
	@ valgrind --leak-check=full ./trab2 test/in/N10_S3_C3_M3.txt out1.txt

valgrind2:
	@ valgrind --leak-check=full ./trab2 test/in/N100_S20_C30_M5.txt out2.txt

valgrind3:
	@ valgrind --leak-check=full ./trab2 test/in/N1000_S50_C300_M10.txt out3.txt

valgrind4:
	@ valgrind --leak-check=full ./trab2 test/in/N10000_S50_C300_M10.txt out4.txt