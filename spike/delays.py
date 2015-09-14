#!/usr/bin/env python3
import optparse

BAUDRATES = [
  115200, 57600, 38400, 31250, 28800, 19200, 
  14400, 9600, 4800, 2400, 1200, 300
]

def cyclesPerMs(cpuFreq, baudrate):
  return (cpuFreq / baudrate) / (cpuFreq / 1000000)
  
def main():
  # Create an instance of the OptionParser, ...
  p = optparse.OptionParser(
      description='Simple script to calculate cpu frequency and baudrate dependend delays when communicating over a serial channel.', 
      prog='delays', version='delays 0.1')

  # ... add all possible options ...
  p.add_option("--code-style", "-c", action="store_true", dest="codeStyle", 
      default=False, help="Print result table in code style")
  p.add_option("--frequency", "-f", action="store", type="int", dest="frequency",
      default=9600, help="CPU frequency used to calculate the delays")
  
  # ... and parse the command line parameters.
  options, arguments = p.parse_args()

  # Display a table of all important delays.
  separator = "+{:-<13}+{:-<13}+{:-<15}+{:-<9}+".format("", "", "", "")

  if options.codeStyle:
    print("{")
  else:
    print("\n" + separator)
    print("| {:>11} | {:>11} | {:>13} | {:>7} |".format(
      "Baudrate", "RX Center", "RX Bit Skip", "TX"))
    print(separator)

  for baudrate in BAUDRATES:
    cycles = cyclesPerMs(options.frequency, baudrate)

    if options.codeStyle:
      print("\t{0}{3:>7}{1}{4:>5}{1}{5:>5}{1}{6:>5}{2},".format(
        '{', ',', '}', baudrate, round(cycles/2), round(cycles), round(cycles-2)))
    else:
      print("| {:>11} | {:>11} | {:>13} | {:>7} |".format(
        round(cycles/2), round(cycles), round(cycles-2)))

  if options.codeStyle:
    print("}")
  else:
    print(separator + "\n")

if __name__ == "__main__":
  main()
