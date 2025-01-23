# Makefile
CC = gcc
CFLAGS = -Wall -Iinclude
OBJDIR = obj
SRCDIR = src
BINDIR = bin
TESTDIR = tests

OBJECTS = $(OBJDIR)/main.o $(OBJDIR)/board.o $(OBJDIR)/game.o $(OBJDIR)/top_players.o
TEST_OBJECTS = $(OBJDIR)/tests.o $(OBJDIR)/board.o $(OBJDIR)/game.o $(OBJDIR)/top_players.o

$(BINDIR)/saper_game: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Testy
tests: $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $(BINDIR)/tests $^

$(OBJDIR)/tests.o: $(TESTDIR)/tests.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/saper_game $(BINDIR)/tests

