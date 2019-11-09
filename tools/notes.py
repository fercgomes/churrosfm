sampleRate = 22050
FCWSize = 100
baseNote = 440
shiftSize = 12
PACSize = 1024

for i in range(FCWSize):
    f = baseNote * pow(2, (i-69 + 36)/12)
    print(str(i) + ":")
    print("freq = " + str(f))
    print("rounded freq = " + str(round(f)))
    freq = round(f) << shiftSize
    print("shifted = " + str(freq))
    val = round((freq * PACSize) / sampleRate)
    print(str(val) + ",")
    print("shifted back = " + str(val >> shiftSize))