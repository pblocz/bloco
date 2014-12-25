SRC = src/
BIN = bin/

BINARY = bloco-c

.phony: start clean

start: $(BIN) $(BIN)$(BINARY)

$(BIN)$(BINARY):
	cd $(SRC); make
	cp $(SRC)build/a.out $(BIN)$(BINARY)


$(BIN):
	mkdir $@

clean:
	cd $(SRC); make clean
	rm -r $(BIN)
