import random

def genTest():
	"""This generates a random version of the input we'll be using for the
	zombie project. It's a little hairy since a lot of the generation is 
	based on my rather arbitrarly picked bounds; you can change them as
	you'd like
	"""	
	#
	'''Descriptors and names gave me an easy way to generate a number of 
	unique zombies. It should be fairly obvious that you can generate
	(descriptor * name) unique zombies for testing. And you can add more 
	descriptors/names if you'd really like more
	'''
	descriptors = ["Big", "Doctor", "Graveyard", 
					"Doctor", "PsychoKiller", "DonaldTrump"]
	names = ["Berta", "Joe", "Bob", "Sam"]


	specialZom = [x + y for x in descriptors for y in names]
	random.shuffle(specialZom)

	'''These are the limiting values for testcases'''
	maxArrows = 10 #upper limit for generated arrows
	seedLim = 999999999 #upper limit for the seed generator number
	distLim = 100000 #upper limit for the maximum distance a zombie spawns
	speedLim = 1000 
	roundLim = random.randint(0, 100)
	zomLim = 200
	specSpeedLim = 2000
	specDistLim = 200000
	roundWeight = 4
	zombieCount = 0
	lineCount = 0

	print "Quiver_Capacity: " + str(random.randint(0, maxArrows))
	print "Random_Seed: " + str(random.randint(0, seedLim))
	print "Max_Rand_Distance: " + str(random.randint(0, distLim))
	print "Max_Rand_Speed: " + str(random.randint(0, speedLim))
	for i in range(roundLim):
		if random.randint(0,roundWeight) and lineCount < 28 and \
			zombieCount < 50:
			print "---"
			print "Round: " + str(i)
			thisZom = random.randint(1, 50  - zombieCount)
			print "Num_Zombies: " + str(thisZom)
			zombieCount += thisZom
			lineCount += 3
			if specialZom:
				thisRdSpec = random.randint(0, 50 - zombieCount)
				for j in range(thisRdSpec):
					if lineCount == 50 or not specialZom:
						break
					thisName = specialZom.pop()
					print str(random.randint(1, specDistLim)) + " " + str(
							random.randint(1, specSpeedLim)) + " " + thisName
					lineCount += 1
					zombieCount += 1

genTest()
