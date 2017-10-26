# Main compiler
CC := g++
# diretorio do source
SRCDIR := .
# diretorio dos arquivos objeto
BUILDDIR := .
#diretorio do executavel
TARGET := Main

# extensao dos fontes
SRCEXT := cpp
# procura todos os fontes
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
# arquivos objeto
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
#parametros de compilacao
CFLAGS := -g
#link para libraries
LIB := -lglut -lGL -lGLU -lm
#includes
INC := -I include


$(TARGET): $(OBJECTS)
	@echo " Linking...";
	@echo " $(CC) $^ -o $(TARGET) $(LIB)";
	$(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<";
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<


clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)";
	$(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean
