

FILE = shell
PTHREAD=-pthread

all:
	gcc $(PTHREAD) $(FILE).c -o $(FILE) -lm

clean:
	rm -rf $(FILE)

