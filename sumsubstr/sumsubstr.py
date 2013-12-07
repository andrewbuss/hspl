def getEqualSumSubstring (s):
	runningtotal = 0
	totals = []
	for digit in s:
		runningtotal += int(digit)
		totals.append(runningtotal)
	totals.append(0) # so that totals[-1] == 0
	longest = 0
	for start in range(len(s)):
		for end in range(start+1,len(s),2):
			midpoint = totals[start+(end-start)/2]
			if midpoint-totals[start-1] == totals[end]-midpoint:
				longest = max(longest,end-start+1)
	print longest

getEqualSumSubstring("986561517416921217551395112859219257312")