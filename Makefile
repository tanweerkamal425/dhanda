CC=gcc
CFLAGS+=-Isrc/include
CFLAGS+=-DTERMINAL_APP

EXECUTABLE=dhanda
DBDIR=~/.dhanda
OBJDIR=.objs
SRCDIR=src
SRCS:=$(shell find $(SRCDIR) -name '*.c')
OBJS:=$(SRCS:src/%=$(OBJDIR)/%.o)
HEADERS:=$(shell find $(SRCDIR) -name *.h)

# If built for PROD then remove debug flag and add optimize flag
ifdef PROD
	CFLAGS+=-O3
else
	CFLAGS+=-g
	CFLAGS+=-DDEBUG
endif

$(EXECUTABLE): $(OBJDIR) $(OBJS)
	$(CC) $(OBJS) -o $@

$(OBJDIR):
	@mkdir $@

$(OBJDIR)/%.c.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -rf $(OBJDIR)

fresh:
	rm -rf $(DBDIR)
