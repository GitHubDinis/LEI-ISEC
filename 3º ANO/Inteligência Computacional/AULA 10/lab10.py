# -*- coding: utf-8 -*-
"""
LAB 10 - 23/24
"""

import gym

env = gym.make("Taxi-v3",render_mode="ansi").env

env.reset()
print(env.render())

print("Action Space {}:".format(env.action_space))
print("State Space {}:".format(env.observation_space))

# env.P[328] -> Reward Table

# env.s = 328
epochs = 0
penalties, reward = 0, 0

done = False

while not done:
    action = env.action_space.sample()
    state, reward, done, info, _ = env.step(action)

    if reward == -10:
        penalties += 1

    epochs += 1
    
print("Timesteps taken: {}".format(epochs))
print("Penalties incurred: {}".format(penalties))
print(env.render())