

FILE = shell
PTHREAD=-pthread

all:
	gcc -w $(PTHREAD) $(FILE).c -o $(FILE) -lm

clean:
	rm -rf $(FILE)

