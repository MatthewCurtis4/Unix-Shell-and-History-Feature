

FILE = shell
PTHREAD=-pthread

all:
	gcc $(PTHREAD) $(FILE).c -o $(FILE)

clean:
	rm -rf $(FILE)

