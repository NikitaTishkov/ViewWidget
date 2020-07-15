CC=gcc
TARGET := vw
LDFLAGS := -lcurl -ljson-c `pkg-config --cflags --libs gtk+-3.0`
CFLAGS := -o2 -std=c17 -rdynamic
SRC := main.c JsonParser.c GetData.c
INC := ./inc
BUILDDIR := .build

.PHONY: clean tidy



$(TARGET): $(addprefix $(BUILDDIR)/,$(SRC:.c=.o))
	$(CC) $(CFLAGS)  $^ -o $@ $(LDFLAGS)

$(BUILDDIR)/main.o: src/main.c $(BUILDDIR)
	$(CC) $(CFLAGS) $(addprefix -I,$(INC)) -c src/main.c -o $@ $(LDFLAGS)

$(BUILDDIR)/JsonParser.o: src/JsonParser.c
	$(CC) $(CFLAGS) $(addprefix -I,$(INC)) -c $< -o $@ -ljson-c

$(BUILDDIR)/GetData.o: src/GetData.c
	$(CC) $(CFLAGS) $(addprefix -I,$(INC)) -c $< -o $@ -lcurl

$(BUILDDIR):
	mkdir $@
	cp ViewWidget.glade $(BUILDDIR)/ViewWidget.glade

clean:
	rm -rf $(BUILDDIR)
	rm -f temp.json

tidy: clean
	rm -f $(TARGET)
