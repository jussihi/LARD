DIRS := doc fs tools

all: $(DIRS)
	$(foreach DIR,$(DIRS),cd $(DIR); make all; cd ..;)

clean: $(DIRS)
	$(foreach DIR,$(DIRS),cd $(DIR); make clean; cd ..;)

doc:
	$(MAKE) -C doc

fs:
	$(MAKE) -C fs

tools:
	$(MAKE) -C tools

.PHONY: all clean $(DIRS) doc fs tools
