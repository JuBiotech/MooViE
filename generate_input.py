import random
import sys

def generate_input(loc, number, inputs, outputs):
 cont = ""
 input_cnt = 1
 output_cnt = 1
 value_cnt = 1

 while input_cnt <= inputs:
  cont += "i#Input" + str(input_cnt) + " [mol],"
  input_cnt += 1
 while output_cnt <= outputs:
  cont += "o#Output" + str(output_cnt) + " [mol]"
  if output_cnt != outputs:
   cont += ","
  output_cnt += 1
 cont += "\n"

 for i in range(number):
  while value_cnt <= inputs + outputs:
   cont += str(random.randint(-100,100))
   if value_cnt != inputs+outputs:
    cont += ","
   value_cnt += 1
  value_cnt = 1
  cont += "\n"

 with open(loc, "w+") as f:
  f.write(cont)
 print("wrote to location " + loc)

if __name__ == "__main__":
 if len(sys.argv) == 5:
  generate_input(sys.argv[1], int(sys.argv[2]), int(sys.argv[3]), int(sys.argv[4]))
