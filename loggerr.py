import argparse, sys, time
import serial
import pandas as pd

parser = argparse.ArgumentParser()
parser.add_argument('--port', required=True, help='Serial port, e.g., COM3 or /dev/ttyACM0')
parser.add_argument('--baud', type=int, default=115200)
parser.add_argument('--outfile', default='data.csv')
args = parser.parse_args()

ser = serial.Serial(args.port, args.baud, timeout=1)
time.sleep(2)  # Wait for Arduino reset

# Read header from Arduino
header = b''
start = time.time()
while time.time() - start < 3:
    line = ser.readline()
    if line:
        header = line
        break

# Set columns
cols = ['timestamp','blinkDuration','ax','ay','az','pitch','roll','mode']
if header:
    h = header.decode('utf-8', errors='ignore').strip().split(',')
    if len(h) == len(cols):
        cols = h

# Create CSV file
with open(args.outfile, 'w', newline='') as f:
    f.write(','.join(cols) + '\n')
    print('Logging... Press Ctrl+C to stop.')
    try:
        while True:
            line = ser.readline()
            if not line:
                continue
            try:
                s = line.decode('utf-8').strip()
                parts = s.split(',')
                if len(parts) != len(cols):
                    continue
                f.write(s + '\n')
            except Exception:
                pass
    except KeyboardInterrupt:
        print('\nStopped.')
    finally:
        ser.close()
