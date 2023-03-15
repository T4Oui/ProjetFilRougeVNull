# Compiler
CC=gcc

# Compiler flags
CFLAGS=-W -Wall -std=c99 -pedantic

# Linker flags
LDFLAGS=-lm

# Source directories
SRC_DIR=./src
TEXT_SRC_DIR=./texte/src
IMAGE_SRC_DIR=./image/src
SON_SRC_DIR=./son/src

# Object directory
OBJ_DIR=./obj

# Object files
OBJ_FILES=$(addprefix $(OBJ_DIR)/, fct_histogrammeV3.o indexationV3.o interface.o recherche_mot_clef.o indexation_texte.o recherche_image.o clean.o tok.o descripteur_Txt.o indexation_image.o pile_dynamique.o tri_fich.o main.o recherche_texte.o table_index.o piles2.o)

# Main target
TARGET=testgen.out

# Default target
all: $(TARGET)

# Clean target
clean:
	rm -rf $(OBJ_FILES) $(TARGET)

# Linking
$(TARGET): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/%.o: $(TEXT_SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/%.o: $(IMAGE_SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/%.o: $(SON_SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

