import time
import numpy as np
import gym
import copy
import chess
import chess.engine


engine = chess.engine.SimpleEngine.popen_uci("stockfish")
limit = chess.engine.Limit(time=2.0)



"""Implementing Welfords Algorithm to store running standard deviation
for multiple values and normalizing observations
"""
class NormalizedObservations(object):
    def __init__(self,observationLen):
        #In states storing tuple of (count,mean,M2)
        self.stats = [(0,0,0) for i in range(observationLen)]

    """Function used to update stats from new observation"""
    def update(self,observation):
        for i in range(len(self.stats)):
            #directly taken from here: https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Welford's_online_algorithm
            (count,mean,M2) = self.stats[i]
            count += 1
            delta = observation[i] - mean
            mean += delta / count
            delta2 = observation[i] - mean
            M2 += delta * delta2
            self.stats[i] = (count,mean,M2)
        
    """Function used to normalize observation"""
    def normalize(self,observation):
        for i in range(len(self.stats)):
            (count,mean,M2) = self.stats[i]
            if  M2 != 0:
                observation[i] = (observation[i] - mean)/(np.sqrt(M2/count)) #M/count is standard deviation
            else:
                #making observation 0 if SDV is going to be zero
                observation[i] = 0

def chessEval(policy,board):
    totalEval = 0
    pieces = ['p','k','r','b','q']
    for i in range(5):
        piece = 
        policy[i]*board.count(piece)
    return totalEval

def playGame(currentPolicy):
    board = chess.Board("1k1r4/pp1b1R2/3q2pp/4p3/2B5/4Q3/PPP2B2/2K5 b - - 0 1")
    agent = chess.MinimaxAgent()
    def evalFunction(board):
        return chessEval(currentPolicy,board)
    agent.evaluationFunction = evalFunction(board)
    result = chess.simulate(engine,agent)
    return result

"""Class for Policy that implements a linear mapping from observation
space to action space.
"""
class Policy(object):
    def __init__(self,environment):
        self.env = gym.make(environment)

        self.observationLen = self.env.observation_space.shape[0]
        self.ActionLen = self.env.action_space.shape[0]

        #Used to store stats for observation normalization
        self.normalizerStats = NormalizedObservations(self.observationLen)

        self.params = np.zeros((self.ActionLen,self.observationLen))
        
    """Get action from policy after normalizing observation"""
    def getAction(self,observation):
        self.normalizerStats.normalize(observation)
        action = self.params.dot(observation) 
        return action

    def update(self,params):
        self.params = params
    
    """Evaluate policy for horizon steps or till completion. delta
       is used to update params for this evaluation but params are
       reset back to old params after evaluation"""
    def evaluate(self,horizon,delta = 0,vis = False,eval = False):

        if delta.all() != 0: 
            oldParams = self.params.copy()
            self.update(self.params + delta)
        observation = self.env.reset()
        totalReward = 0
        
        for t in range(horizon):
            for i in range(20):
                totalReward += playGame

        if delta.all() != 0: self.update(oldParams)
        return totalReward


def train_policy(policy,iterations,horizon,stepSize,N,noise,b):  
    for iter in range(iterations):

        if iter%1== 0:
            print("In interation " + str(iter))
            #print("Current Reward: " + str(policy.evaluate(horizon,0,eval = True)))


        #printing policy after every 100 iterations for debugging

        rewards = []
        for k in range(N):
            #generating deltas
            randomDelta = np.random.random((policy.ActionLen,policy.observationLen))

            #get rewards for positive and negative shifts
            rewardPos = policy.evaluate(horizon,noise*randomDelta)
            rewardNeg = policy.evaluate(horizon,noise*(-randomDelta))
    
            rewards.append(((rewardPos,rewardNeg),randomDelta))

        #Sort rewards by max(rewardPos,rewardNeg) for each delta in ascending order
        rewards = sorted(rewards,key = lambda a : max(a[0]),reverse=True)

        #Calculate sum of b best deltas for update of policy
        update_sum = np.zeros((policy.ActionLen,policy.observationLen))
        for i in range(b):
            (rewardPos,rewardNeg),delta = rewards[i]
            update_sum += (rewardPos - rewardNeg)*delta

        #Calculating standard deviation of b best deltas
        bestRewards = []
        for i in range(b):
            bestRewards += [rewards[i][0]]
        sdvBestRewards = np.std(np.array(bestRewards))

        if sdvBestRewards != 0:
            policy.update(policy.params + update_sum*(stepSize/(b*sdvBestRewards)))

if __name__ == "__main__":
    policy = [0,0,0,0,0]
    train_policy(new_policy,2300,1600,0.01,16,0.02,8) 
    print("Training Done")
    serializedPolicy = np.array([new_policy.params,new_policy.normalizerStats.stats],dtype=object)
    np.save("policy",serializedPolicy)
