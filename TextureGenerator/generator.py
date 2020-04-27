from PIL import Image
import sys

s_inputImage = ""
s_outputBinary = ""
image_InputImage = None
if(len(sys.argv) > 1):
    try:
        s_inputImage = sys.argv[1]
        s_outputBinary = sys.argv[2]
    except:
        sys.stderr.write("Output filename required!\nUsage generator.py [inputImage] [outputFile]")
        exit()
    
else:
    sys.stderr.write("Input & Output filenames are required!\nUsage generator.py [inputImage] [outputFile]")
    exit()


try:
    image_InputImage = Image.open(s_inputImage)
except:
    sys.stderr.write("No such file named \"" + s_inputImage + "\"")

n_ImageWidth = image_InputImage.width;
n_ImageHeight = image_InputImage.height;

b_outputByteArray = bytearray([0x0] * (n_ImageWidth * n_ImageHeight*3 + 8))

with open(s_outputBinary,"wb") as out_file:
    out_file.write(b_outputByteArray)
