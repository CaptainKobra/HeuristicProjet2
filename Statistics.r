#Read the data in the csv file
#The data is sorted by algorithm and each algoithm as been run 5 times on each of the 10 instances
#The first colum is for the score obteined, the second for the time taken to compute the solution
#and the third for the best known score for the instance

###############
#LOCAL SEARCH PART#
##############

data_50 <- read.csv("./PFSP_instances/50/results50.csv" ,sep = ",")
data_100 <- read.csv("./PFSP_instances/100/results100.csv", sep = ",")


arr_ls <- array(0, dim = c(12, 4), dimnames = list(c("t.f.RZ", "t.f.r", "t.b.RZ", "t.b.r", "e.f.RZ", "e.f.r", "e.b.RZ", "e.b.r", "i.f.RZ", "i.f.r", "i.b.RZ", "i.b.r"), c( "average time 50 (µ s)", "%deviation 50", "average time 100 (µ s)", "%deviation 100")))

#for each algorithm, calculate the average time taken to compute the solution
i <- 1
pos <- 1
while (i <= 12) {
    arr_ls[i, 1] <- mean(data_50[pos:pos+49, 2])
    arr_ls[i,3] <- mean(data_100[pos:pos+49, 2])
    pos <- pos + 50
    i <- i + 1
}

calculate_deviation <- function(raw) {
    return (100 * (raw[1] - raw[3]) / raw[3])
}

#for each algorithm, calculate the % deviation from the best known score
i <- 1
pos <- 1
while (i <= 12) {
    arr_ls[i, 2] <- mean(apply(data_50[pos:pos+49,], 1, calculate_deviation))
    arr_ls[i,4] <- mean(apply(data_100[pos:pos+49,], 1, calculate_deviation))
    pos <- pos + 50
    i <- i + 1
}

#Wilcoxon tests for initial solution : RZ vs random
#t.f.RZ vs t.f.r
RZ.vs.random <- wilcox.test(apply(data_50[1:50,],1,calculate_deviation), apply(data_50[51:100,],1,calculate_deviation), alternative = "two.sided", paired = TRUE)$p.value

#Wilcoxon tests for pivoting rule quality : first vs best
#t.f.RZ vs t.b.RZ
first.vs.best.quality <- wilcox.test(apply(data_50[1:50,],1,calculate_deviation), apply(data_50[101:150,],1,calculate_deviation), alternative = "two.sided", paired = TRUE)$p.value

#Wilcoxon tests for pivoting rule speed : first vs best
#t.f.RZ vs t.b.RZ
first.vs.best.speed <- wilcox.test(data_50[1:50,2], data_50[101:150,2], alternative = "two.sided", paired = TRUE)$p.value


#Wilcoxon test for neighborhood quality : exchange vs insert
#e.f.RZ vs i.f.RZ
exchange.vs.insert <- wilcox.test(apply(data_50[201:250,],1,calculate_deviation), apply(data_50[401:450,],1,calculate_deviation), alternative = "two.sided", paired = TRUE)$p.value

#Wilcoxon test for neighborhood speed : exchange vs insert
#e.f.RZ vs i.f.RZ
exchange.vs.insert <- wilcox.test(data_50[201:250,2], data_50[401:450,2], alternative = "two.sided", paired = TRUE)$p.value


print(arr_ls)

#Print the results
print("Wilcoxon tests for initial solution : RZ vs random")
print(RZ.vs.random)
print("Wilcoxon tests for pivoting rule quality : first vs best")
print(first.vs.best.quality)
print("Wilcoxon tests for pivoting rule speed : first vs best")
print(first.vs.best.speed)
print("Wilcoxon test for neighborhood quality : exchange vs insert")
print(exchange.vs.insert)
print("Wilcoxon test for neighborhood speed : exchange vs insert")
print(exchange.vs.insert)

###############
####VND PART####
##############

#VND
data_50_VND <- read.csv("./PFSP_instances/50/results50_VND.csv" ,sep = ",")
data_100_VND <- read.csv("./PFSP_instances/100/results100_VND.csv", sep = ",")

arr_VND <- array(0, dim = c(4, 4), dimnames = list(c("teiRZ", "tei.r", "tie.RZ", "tie.r"), c( "average time 50 (µ s)", "%deviation 50", "average time 100 (µ s)", "%deviation 100")))

calculate_deviation <- function(raw) {
    return (100 * (raw[1] - raw[3]) / raw[3])
}

i <- 1
pos <- 1
while (i <= 4) {
    arr_VND[i, 1] <- mean(data_50_VND[pos:pos+9, 2])
    arr_VND[i,3] <- mean(data_100_VND[pos:pos+9, 2])
    pos <- pos + 10
    i <- i + 1
}

i <- 1
pos <- 1
while (i <= 4) {
    arr_VND[i, 2] <- mean(apply(data_50_VND[pos:pos+9,], 1, calculate_deviation))
    arr_VND[i,4] <- mean(apply(data_100_VND[pos:pos+9,], 1, calculate_deviation))
    pos <- pos + 10
    i <- i + 1
}

print(arr_VND)

#Wilcoxon tests for initial solution quality : RZ vs random
#teiRZ vs tei.r
RZ.vs.random.quality <- wilcox.test(apply(data_50_VND[1:10,],1,calculate_deviation), apply(data_50_VND[11:20,],1,calculate_deviation), alternative = "two.sided", paired = TRUE)$p.value

#Wilcoxon tests for initial solution speed : RZ vs random
#teiRZ vs tei.r
RZ.vs.random.speed <- wilcox.test(data_50_VND[1:10,2], data_50_VND[11:20,2], alternative = "two.sided", paired = TRUE)$p.value

#Wilcoxon tests for ordering permutation quality : tei vs tie
#teiRZ vs tie.RZ
tei.vs.tie.quality <- wilcox.test(apply(data_50_VND[1:10,],1,calculate_deviation), apply(data_50_VND[21:30,],1,calculate_deviation), alternative = "two.sided", paired = TRUE)$p.value

#Wilcoxon tests for ordering permutation speed : tei vs tie
#teiRZ vs tie.RZ
tei.vs.tie.speed <- wilcox.test(data_50_VND[1:10,2], data_50_VND[21:30,2], alternative = "two.sided", paired = TRUE)$p.value


#Print the results
print("Wilcoxon tests for initial solution quality : RZ vs random")
print(RZ.vs.random.quality)
print("Wilcoxon tests for initial solution speed : RZ vs random")
print(RZ.vs.random.speed)
print("Wilcoxon tests for ordering permutation quality : tei vs tie")
print(tei.vs.tie.quality)
print("Wilcoxon tests for ordering permutation speed : tei vs tie")
print(tei.vs.tie.speed)


###############
####LS vs VND####
##############

#wilcoxon test for LS vs VND quality : i.b.RZ vs teiRZ
LS.vs.VND.quality <- wilcox.test(apply(data_50[501:510,],1,calculate_deviation), apply(data_50_VND[1:10,],1,calculate_deviation), alternative = "two.sided", paired = TRUE)$p.value

#wilcoxon test for LS vs VND speed : i.b.RZ vs teiRZ
LS.vs.VND.speed <- wilcox.test(data_50[501:510,2], data_50_VND[1:10,2], alternative = "two.sided", paired = TRUE)$p.value


#Print the results
print("wilcoxon test for LS vs VND quality : i.b.RZ vs teiRZ")
print(LS.vs.VND.quality)
print("wilcoxon test for LS vs VND speed : i.b.RZ vs teiRZ")
print(LS.vs.VND.speed)



