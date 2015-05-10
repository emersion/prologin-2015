# -*- coding: utf-8 -*-
#
# Schroder
#
# Features:
# * A fun and unique welcome message at the begining of THE GAME.
# * YTP-ready info messages.
#
# Changelog:
# * Added one more welcome message for more sausage.
#
# Fonctionne principalement grace a un system de score associe a 
# chaque objectif.
#

from api import *
import random
from utils import *
from agent import Agent
from history import History
import target

agent = None
history = None

# Fonction appelée au début de la partie.
def partie_init():
	global agent # TODO: this is awful
	global history # TODO: this is like Microsoft Windows(R)

	agent = Agent()
	history = History()

	target.set_ctx(agent, history)

	welcome()

# Fonction appelée à chaque tour.
def jouer_tour(child=False):
	global agent # TODO: this is bad
	global history # TODO: this is ugly

	updated_target = None # Next target

	if agent.remaining_dist == 0:
		if agent.target is not None: # Target reached
			# # Check if target is up-to-date
			# if child == False:
			# 	t = target.find()
			# 	if t is not None and t != agent.target:
			# 		#warn("OUTDATED_TARGET", "preturn_find_target")
			# 		updated_target = t
			# 		warn("TARGET_CORRECTED", "preturn_find_target")

			# Detect static point
			if len(history.created_portals) > 2 and history.created_portals[-1] == agent.target and history.created_portals[-2] == agent.target:
				ds = history.score_delta()
				if ds[0] <= ds[1]:
					# Move on
					updated_target = target.find(blacklist=agent.target)

			if not updated_target:
				# On s'occupe de la cible
				owner = portail_joueur(agent.target)
				if owner == adversaire(): # Neutralize
					err = neutraliser()
					if err == erreur.PA_INSUFFISANTS:
						info("Cannot kill enemy portal for now, skipping turn...")
						return "STOP"
					elif err != erreur.OK:
						warn(err, "kill")

				if owner != moi(): # Capture
					err = capturer()
					if err == erreur.PA_INSUFFISANTS:
						info("Cannot create new portal for now, skipping turn...")
						return "STOP"
					elif err != erreur.OK:
						warn(err, "p0wn")
					else:
						history.portal_created(agent.target)

				for p in portals_by_player(moi()): # Add links
					err = lier(p)
					if err == erreur.PA_INSUFFISANTS:
						#warn(err, "link")
						info("Cannot create new links for now, skipping turn...")
						return "STOP"
					else:
						pass # TODO: handle err?

				# Add schields
				links_count = len(liens_incidents_portail(agent.target))
				while portail_boucliers(agent.target) < min(links_count, 3):
					err = ajouter_bouclier()
					if err == erreur.PA_INSUFFISANTS:
						info("Cannot create new shields for now, skipping turn...")
						return "STOP"
					elif err != erreur.OK:
						break # TODO: handle err?

		# Find a new target
		if updated_target is None:
			updated_target = target.find()
		if updated_target is None:
			warn("NO_MORE_TARGET", "find_target")
			return "NO_MORE_TARGET"
	else:
		if agent.target is not None:
			# Check if target is up-to-date
			if child == False: # ... Only if we are at the begining of the turn
				t = target.find()
				if t is not None and t != agent.target:
					#warn("OUTDATED_TARGET", "preturn_find_target")
					updated_target = t
					warn("TARGET_CORRECTED", "preturn_find_target")

	# Check for cyclic behaviours
	if updated_target is not None:
		if history.prevent_cyclic_behaviour(updated_target):
			warn("CYCLIC_TARGET_DETECTED", "find_target")
			blacklisted = updated_target
			updated_target = target.find(blacklist=blacklisted)
			if updated_target is None: # Could not find an alternative
				warn("USED_BLACKLISTED_TARGET", "find_target")
				updated_target = blacklisted

		agent.set_target(updated_target)

	# Use turbo to reach target
	if points_deplacement() < agent.remaining_dist and points_action() > 0:
		while points_deplacement() < agent.remaining_dist:
			if points_action() < COUT_TURBO:
				break
			utiliser_turbo()

	# Reach target
	err = agent.do_target()
	if err == "PENDING" or err == "NOOP":
		return "MOVING"
	if err != erreur.OK:
		warn(err, "agent.do_target")

	# Can we do something more during this turn?
	if agent.remaining_dist == 0 and (points_action() > 0 or points_deplacement() > 0):
		result = jouer_tour(True)

		if result != None:
			# End of turn, do minor actions if possible
			pos = position_agent(moi())

			if points_action() > 0:
				if pos in liste_portails() and portail_joueur(pos) == moi():
					# Add shields
					i = 0
					while True:
						err = ajouter_bouclier()
						if err == erreur.PA_INSUFFISANTS:
							break
						elif err != erreur.OK:
							warn(err, "postturn_add_shields")
							break
						i += 1
					info("Created "+str(i)+" shields, "+str(points_action())+" remaining actions")
				else:
					# Execute secoundary targets
					blacklisted = [agent.target]
					for i in range(3):
						sec_cost = 0
						sec_target = target.find(blacklist=blacklisted)
						sec_dist = distance(pos, sec_target)
						move_cost = (sec_dist - points_deplacement()) * COUT_TURBO
						if points_action() >= move_cost + target_cost(sec_target):
							info("CAN_EXECUTE_SECOUNDARY_TARGET:"+repr(sec_target), "find_secoundary_target")
							primary_target = agent.target
							agent.set_target(sec_target)
							agent.do_target()
							jouer_tour(True)
							agent.set_target(primary_target)
						blacklisted.append(sec_target)
					if len(blacklisted) == 5:
						info("Cannot use remaining "+str(points_action())+" actions")

			info("End of Turn. PA: "+str(points_action())+", PD: "+str(points_deplacement()))

			history.turn_finished(agent.target)

	return None

# Fonction appelée à la fin de la partie.
def partie_fin():
	my_score = score(moi())
	enemy_score = score(adversaire())
	if my_score == enemy_score:
		print("OH BABY IT'S A TRIPLE!!1")
	elif my_score > enemy_score:
		print("C'est royal !")
	else:
		print("Je regrette, mais c'est vraiment non.")
