from api import *
from utils import *

def get_scores_tuple():
	return score(moi()), score(adversaire())

class History:
	def __init__(self):
		self.targets = []
		self.scores = []
		self.created_portals = []
		self.created_portals_scores = []
		self.cyclic_targets = []

	def turn_finished(self, target):
		self.targets.append(target)
		self.scores.append(get_scores_tuple())

	def portal_created(self, pos):
		self.created_portals.append(pos)
		self.created_portals_scores.append(get_scores_tuple())

	def score_delta(self, turns_delta=1):
		if len(self.scores) < turns_delta:
			return (0, 0)

		current_scores = get_scores_tuple()
		last_scores = self.scores[-turns_delta]
		return (current_scores[0] - last_scores[0],
			current_scores[0] - last_scores[1])

	def is_target_cyclic(self, target):
		if len(self.scores) < 4:
			return False

		max_depth = 15
		min_depth = 2

		l = len(self.created_portals)

		i = 0
		found = False
		for j in range(2, min(l, max_depth)):
			i = l - j
			if self.created_portals[i] == target:
				found = True
				break
		if not found:
			return False

		#print("[DEBUG][history][1]", i, target, self.created_portals[l-max_depth:])

		for diff in range(1, min_depth+1):
			a = i - diff
			b = l - diff

			#print("[DEBUG][history][2]", a, b)

			if self.created_portals[a] != self.created_portals[b]:
				return False

		delta_scores = self.score_delta(i - l)
		#print("[DEBUG][history][3]", "WOOOOOWOOOOOOOWOOWOOOOWOOOOOW:"+repr(delta_scores), l-i)
		if delta_scores[0] == delta_scores[1]:
			return (score(moi()) < score(adversaire()))
		else:
			return (delta_scores[0] < delta_scores[1])

	def prevent_cyclic_behaviour(self, target):
		is_cyclic = self.is_target_cyclic(target)
		if not is_cyclic:
			return False

		self.cyclic_targets.append((target, tour_actuel()))

		return True

	def was_target_cyclic(self, target):
		turn = tour_actuel()
		for t in self.cyclic_targets:
			if turn > t[1] + 2:
				self.cyclic_targets.remove(t)
				continue
			if t[0] == target:
				return True
		return False