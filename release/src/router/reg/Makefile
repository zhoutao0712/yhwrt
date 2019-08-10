EXEC = reg

all:
	- cp prebuild/reg reg
	- cp prebuild/switch switch

install: all
	install -D $(EXEC) $(INSTALLDIR)/bin/$(EXEC)
	$(STRIP) $(INSTALLDIR)/bin/$(EXEC)
	install -D switch $(INSTALLDIR)/bin/switch
	$(STRIP) $(INSTALLDIR)/bin/switch

clean:
	-rm -f $(EXEC) *.elf *.gdb *.o switch
