import sys
import os

def tob26(line):
	val = 0
	for i, ch in enumerate(line):
		x = ch - ord('a')
		val = val + x * 26 ** i
	return val

def encode_var_l(word26):
	result = []
	while word26 > 0:
		#use 7bit bytes and use bit 8 to indicate if the next byte is a continuation
		num = word26 & 0x7F
		word26 = word26 >> 7
		if word26 > 0:
			num |= 0x80			
		result.append(num)
	return result


def encode_word_file(filename, prefix):

	header_file_name = prefix + ".h"
	source_file_name = prefix + ".c"	
	prefix = os.path.split(prefix)[1]
	header_file = open(header_file_name,"w")
	source_file = open(source_file_name,"w")

	header_file.write("#ifndef __" + prefix.upper() + "_H__\n")
	header_file.write("#define __" + prefix.upper() + "_H__\n")

	source_file.write("#include \"" + prefix + ".h\"\n")


	words_metadata = []

	f = open(filename)
	lines = f.readlines()
	f.close()

	buckets = dict()
	total_bytes = 0
	
	for line in lines:
		arr = buckets.get(line[0], [])
		arr.append(line)
		buckets[line[0]] = arr

	for ch in "abcdefghijklmnopqrstuvwxyz" :
		arr = buckets.get(ch, [])
		arr.sort()
		current = 0
		bytes_arr = []
		bytes_count = 0
		for line in arr:
			source = line.strip().encode('ascii').lower()
			new_line = source[1:]
			new_line = new_line[::-1]

			val = tob26(new_line)
			delta = val - current
			current = val
			barr = encode_var_l(delta)
			bytes_arr.append((source, barr, val, delta))
			bytes_count += len(barr)
		if len(bytes_arr) > 0:
			array_name = prefix.upper() + "_"  + ch.upper()
			header_file.write("extern const unsigned char " + array_name + "[];\n");
			source_file.write("const unsigned char " + array_name + "[" + str(bytes_count) +"] =  {\n")
			for data_point in bytes_arr:
				source_file.write("/*" + str(data_point[0]) + " = " + str(data_point[2]) + ", delta = " + str(data_point[3]) + "*/\n");
				for bt in data_point[1]:
					source_file.write(str(bt) + ", ");
				source_file.write("\n")			
			source_file.write("};\n")
			total_bytes += bytes_count
			words_metadata.append((array_name, len(bytes_arr)))
		else:
			words_metadata.append(("0", 0))
	
	header_file.write("\nextern const unsigned char* " + prefix.upper() + "_START[];\n");
	header_file.write("\nextern const unsigned short " + prefix.upper() + "_SIZE[];\n");

	source_file.write("const unsigned char* " + prefix.upper() + "_START[26] = {\n");
	for i in words_metadata:
		source_file.write(i[0] + ",\n")
	source_file.write("};\n")
	
	source_file.write("const unsigned short " + prefix.upper() + "_SIZE[26]={\n");
	for i in words_metadata:
		source_file.write(str(i[1]) + ",\n")
	source_file.write("};\n")


	source_file.close()
	header_file.write("#endif\n")
	header_file.close()
	return (total_bytes, len(lines))


if len(sys.argv) < 3:
	print("Usage : build_words_db.py <input file name> <output file name>")
else:
	guess = encode_word_file(sys.argv[1], sys.argv[2])
	print("DB words count : " + str(guess[1]) + ", bytes compressed : " +  str(guess[0]))


