"""
Distance3.py
Display analog data from Arduino using Python (matplotlib)
Authors: Robert Horvers & Evert Poots
"""

import sys, serial, argparse
import numpy as np
from time import sleep
from collections import deque

import matplotlib.pyplot as plt 
import matplotlib.animation as animation

    
# plot class
class AnalogPlot:
  # constr
  def __init__(self, strPort, maxLen):
      # open serial port
      self.ser = serial.Serial(strPort, 9600)

      self.aA = deque([0.0]*maxLen)
      self.aB = deque([0.0]*maxLen)
      self.aC = deque([0.0]*maxLen)
      self.aD = deque([0.0]*maxLen)
      self.maxLen = maxLen

  # add to buffer
  def addToBuf(self, buf, val):
      if len(buf) < self.maxLen:
          buf.append(val)
      else:
          buf.pop()
          buf.appendleft(val)

  # add data
  def add(self, data):
      assert(len(data) == 4)
      self.addToBuf(self.aA, data[0])
      self.addToBuf(self.aB, data[1])
      self.addToBuf(self.aC, data[2])
      self.addToBuf(self.aD, data[3])

  # update plot
  def update(self, frameNum, a0, a1, a2, a3):
      try:
          line = self.ser.readline()
          data = [float(val) for val in line.split()]
          # print data
          if(len(data) == 4):
              self.add(data)
              a0.set_data(range(self.maxLen), self.aA)
              a1.set_data(range(self.maxLen), self.aB)
              a2.set_data(range(self.maxLen), self.aC)
              a3.set_data(range(self.maxLen), self.aD)

      except KeyboardInterrupt:
          print('exiting')
      
      return a0, 

  # clean up
  def close(self):
      # close serial
      self.ser.flush()
      self.ser.close()    

# main() function
def main():
  # create parser
  parser = argparse.ArgumentParser(description="LDR serial")
  # add expected arguments
  parser.add_argument('--port', dest='port', required=True)

  # parse args
  args = parser.parse_args()
  
  #strPort = '/dev/tty.usbserial-A7006Yqh'
  strPort = args.port

  print('reading from serial port %s...' % strPort)

  # plot parameters
  analogPlot = AnalogPlot(strPort, 100)

  print('plotting data...')

  # set up animation
  fig = plt.figure()
  ax = plt.axes(xlim=(0, 100), ylim=(0, 500))
  a0, = ax.plot([], [])
  a1, = ax.plot([], [])
  a2, = ax.plot([], [])
  a3, = ax.plot([], [])
  anim = animation.FuncAnimation(fig, analogPlot.update, 
                                 fargs=(a0, a1, a2, a3), 
                                 interval=50)
  
  # show plot
  plt.show()
  
  # clean up
  analogPlot.close()

  print('exiting.')
  

# call main
if __name__ == '__main__':
    main()
