from api import *
from utils import *

class Agent:
	def __init__(self):
		self.target = None
		self.remaining_dist = 0

	def pos(self):
		return position_agent(moi())

	def set_target(self, target):
		self.target = target
		self.remaining_dist = distance(self.pos(), self.target)

	def do_target(self):
		if self.target is None:
			return "AUCUNE_POSITION"

		if self.remaining_dist == 0:
			return "NOOP"

		pos = self.pos()
		dx = self.target[0] - pos[0]
		dy = self.target[1] - pos[1]

		if dx != 0 and points_deplacement() > 0:
			dx_dir = int(dx/abs(dx))
			if points_deplacement() < abs(dx):
				dx = dx_dir * points_deplacement()
			new_pos = (pos[0] + dx, pos[1])
			err = deplacer(new_pos)
			if err == erreur.OK:
				pos = new_pos
			else:
				warn(err, "do_target_x")

		if dy != 0 and points_deplacement() > 0:
			dy_dir = int(dy/abs(dy))
			if points_deplacement() < abs(dy):
				dy = dy_dir * points_deplacement()
			new_pos = (pos[0], pos[1] + dy)
			err = deplacer(new_pos)
			if err != erreur.OK:
				warn(err, "do_target_y")

		self.remaining_dist = distance(self.pos(), self.target)

		if self.remaining_dist == 0:
			return erreur.OK
		return "PENDING"