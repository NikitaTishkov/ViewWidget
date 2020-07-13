CC=gcc
TARGET := vw
LDFLAGS := -lcurl -ljson-c `pkg-config --cflags --libs gtk+-3.0`
CFLAGS := -o2 -std=c17 -rdynamic
SRC := main.c JsonParser.c GetData.c
BUILDDIR := build

.PHONY: clean tidy



$(BUILDDIR)/$(TARGET): $(addprefix $(BUILDDIR)/,$(SRC:.c=.o))
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILDDIR)/main.o: src/main.c $(BUILDDIR)
	$(CC) $(CFLAGS) -c src/main.c -o $@ $(LDFLAGS)

$(BUILDDIR)/JsonParser.o: src/JsonParser.c
	$(CC) $(CFLAGS) -c $< -o $@ -ljson-c

$(BUILDDIR)/GetData.o: src/GetData.c
	$(CC) $(CFLAGS) -c $< -o $@ -lcurl

$(BUILDDIR):
	mkdir $@
	cp ViewWidget.glade $(BUILDDIR)/ViewWidget.glade

clean:
	rm -f $(BUILDDIR)/$(SRC:.o=.c)

tidy:
	rm -rf $(BUILDDIR)