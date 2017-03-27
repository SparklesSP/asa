unparsed = open("unparsed.txt", "r").read().split("----------")[1:]

parsed = [open("9", "w"), open("10", "w"), open("11", "w"), open("12", "w"), open("13", "w"), open("14", "w"), open("15", "w")]
i = -1

for i in range(len(unparsed) - 1):
    parsed[i].write(unparsed[i].rstrip().lstrip())
    parsed[i].write("\n")
    parsed[i].close()
