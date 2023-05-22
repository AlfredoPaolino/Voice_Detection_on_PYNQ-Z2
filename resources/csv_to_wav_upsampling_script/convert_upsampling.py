#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import array
import numpy as np
import scipy.io.wavfile
from scipy.io.wavfile import write
from scipy.signal import resample
from numpy import *

samplerate = 16000

csv_matrix = np.loadtxt('../D_ST_Client/output/aud_0.csv', delimiter=',', dtype=int16)

csv_array = np.array(csv_matrix).flatten()

csv_array_upsampled = []

for i in range(0,len(csv_array)-2):
	csv_array_upsampled.append(csv_array[i])
	csv_array_upsampled.append(int((csv_array[i]+csv_array[i+1])>>1))

csv_array_upsampled.append(csv_array[len(csv_array)-1])

#print(len(csv_array_upsampled))
#print("\n\n")
#print(len(csv_matrix))
#print(len(csv_matrix[0]))
#print("\n\n")
#print(csv_matrix)
#print("\n\n")
#print(csv_array_upsampled)
#print("\n\n")

data_resampled = resample(np.array(csv_array_upsampled), samplerate)

print(data_resampled)
print(len(data_resampled))

#scipy.io.wavfile.write('output.wav', samplerate, data_resampled)

write("output/recorded.wav", samplerate, np.array(csv_array_upsampled).astype(np.int16))
