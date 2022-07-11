# Troubleshooting, Investigation, & Thought-Process

A detailed, chronological recount of my troubleshooting/investigation steps and thoughts at the time.

## Summary
- Pulling the middle 3.3V pin in DE9 connector on Bass Module LOW significantly loads the SmartSpeaker data line voltage, destroying the signal.
	- This causes the random freezes and shutdowns.
- The Console unit does not output a left-channel signal when using any analog input source. I suspect this could be an issue with U4000.
- The fastest and simplest solution for me was to just re-create the core functionality that I need using an Arduino, IR receiver, and some other components.

See the [README.md](README.md) document for the initial symptoms that I noted.

---
## Steps
01. Noted issues explained in Introduction.
02. Suspect a surge triggered the problem, regardless of location.
03. Learned about voltages in Console [0, pg4] and suspected the 1.8V line for CPU was browning out / failing, causing the crashes.
04. Opened console and checked 3.3V and 1.8V regulators; all good, no VCC problems.
05. Read that Console has brownout detection [0, pg6] via monitoring V_UNREG (basically rectified tap from transformer), and will mute/shutdown to prevent audio pops.
06. Suspect that surge fried the brownout detection circuit/pin, resulting in random false triggers, causing unexpected shutdowns.
07. Researched pinout of 13-pin Acoustimass connector (see [Pinouts.md](Pinouts.md)) and tested voltages on Bass Module with all else disconnected.
	- Some pins have voltages that disagree with their expected purpose.
	- Expected Mute pin (4) to be at 3.3V, but was hovering around 1.1V.
	- Expected DSP_Shutdown pin (5) to be at 0v0/3v3/5v0 (as its disabled), but was floating around 1V
	<details>
	<summary><b>TABLE: Bass Module Acoustimass Connector Voltages</b></summary>

	Pin # | Module Sleeping, No Console | Module Awake, No Console
	--- | --- | ---
	1 | 29.0V | 28.1V
	2 | GND | GND
	3 | 0.78V (diode?) | 0.91V
	4 | 1.19V | 1.15V
	5 | 1.06V | 1.06V
	6 | 0V | 0V
	7 | 0V | 0V
	8 | 0V | 0V
	9 | 0V | 0V
	10 | 0V | 0V 
	11 | 0.78V (diode?) | 0.93V
	12 | 0V | 0V
	13 | 3.26V | 2.85V
	</details>
08. Learned that Pin13 (SmartSpeaker) is required to turn the Bass Module on, and that all the amp/control circuits are actually in there.
09. Learned (and verified via sticking pins into socket) that raw analog signals can be sent through the 13-pin connector to be played by the Bass Module.
	- Required turning the Bass Module using the Console ("tricking it on") and then disconnecting the 13-pin cable.
10. Assuming Console is un-repairable, decided to design basic replacement Console using an Arduino and supporting components.
	- Our usage only involves external analog audio sources, so the Console was simply acting as a mixer and serial interface.
	- Planned to "snoop" serial data and mimic the SmartSpeaker protocol with an Arduino, then just feed raw analog audio to the Bass Module.
11. Soldered wires onto pin2 (GND) and pin13 (SmartSpeaker) on Bass Module PCB, reconnected to Console & Satellite Speakers, and began viewing serial data on oscilloscope.
	- Noted the Vpp of signal was 1.78V, whereas it should have been 3.3V or 5.0V.
	- Noted that the voltage OCCASIONALLY/RANDOMLY would pop back up to 5V, and that the problems (random shutdowns, etc.) only occurred when the voltage was in 1.78V levels.
12. Realized that unplugging the 9-pin DE9 Satellite Speaker connector from the Bass Module restored the serial voltage to 5V.
13. Checked voltage on pin13 on Bass Module when unplugged from Console and found ~0.5V avg when DE9 connector is in place, but ~3.3V avg when unplugged.
	- Conclusion: The problem appears to be located in the Bass Module, and that the Console is probably fine.
14. Tested voltages on DE9 connector on Bass Module, noted 3.3V potential on middle pin (again, see Pinouts.md).
15. Tested pinout on Satellite Speaker cable and learned that the middle pin with 3.3V is connected to SHIELD (which gets grounded on the Bass Module)
16. Suspect that the pin is either erroneously high (and connecting the cable shorts it to GND through shield, thus collapsing the Bass Module's 3.3V supply and causing the problem *ALTHOUGH there is supposed to be a circuit that triggers a reset [0, pg22] if voltage drops below 3.08V, so maybe PSU is still okay*), OR maybe it's intentional and used as a sense line that, when pulled low by the cable, indicates the Satellite Speakers are present and some other circuitry (amp?) may activate.
17. Successfully connected an external speaker into Bass Module's DE9 connector without connecting centre 3.3V pin to GND and got playback.
	- Connecting the pin to GND does not change volume at all (but problems immediately return)
18. Theorize that something is wrong on the Bass Module board to cause 3.3V to appear on that pin. It may supposed to be an ANALOG_GND pin and some chip is fried and pulling it high?
19. If desperate later, I plan to cut the trace on the PCB leading to that (3.3V) pin on the DE9, as it doesn't seem to be required for basic analog audio playback.
	- Still bothersome as there is clearly a problem somewhere.
20. Attempted to determine the actual DE9 pinout; while doing so, ran a left/right audio test.
	- Noted that the left channel appears to be completely dead (Bass driver doesn't even work for left channel when DE9 is disconnected).
21. "Tricked" Bass Module on again and manually sent analog audio through the 13-pin connector again; both left and right (woofer & treble) work fine.
	- Left audio channel problem is within the Console
22. Reconnected Console to Bass Module and cycled through all input ports (AUX/TV/CBL•SAT); seems Console is not sending left-channel audio.
	- Alternatively it could just be muting the channel for some reason? I doubt that.
	- Theorize that the problem could like within U4000 (a TEA6422; 6-input stereo analog input MUX chip) [0, pg8] could be the problem. Should test by using something with a digital source (eg. DVD)
23. Decided that, for now, cannot repair Console as easily as could just build a custom Arduino replacement.
	- Set Console and 13-pin Acoustimass cable aside; want new solution to be completely non-destructive so a revisit in the future is possible.
24. Connected an Arduino Uno in RX-only mode to GND and SmartSpeaker breakout wires on the Bass Module & began reverse-engineering the protocol (see [SmartSpeakerProtocol.md](SmartSpeakerProtocol.md)] for details).
	- Struggled to understand many commands.
25. Realized that the Console box still has a Boselink/ETAP port available (See [Pinouts.md](Pinouts.md)); could potentially connect to it and send known-commands to Console, and relate it to the data the Console sends to the Bass Module. See [ETAPProtocol.md](ETAPProtocol.md) for my quick notes on the topic.
26. Found pinout (see [Pinouts.md](Pinouts.md)) and connected using an Arduino (using SoftSerial) and attempted to send ETAP commands.
	- Used commands found in [1, pg72] but was unable to get expected responses.
27. Gave up on ETAP commands (for now) as couldn't find a coherent source for them either. Will have to revisit later too.
28. Tested the (limited) reverse-engineered SmartSpeaker commands using the Arduino Uno hooked to the Bass Module successfully
	- Was able to turn on, change volume, mute, turn off
29. Noticed that plugging in DE9 connector doesn't drop serial voltage while using JUST the Arduino; more testing needed.
30. 3.3V signal is still present on DE9, and now the serial voltage remains stable with DE9 connected (testing with both Arduino and original Console).
	- Appears the serial data issue is inconsistent. I think it's best to just cut the trace anyways (The left-channel audio problem is still present with the Console).
31. Opened up the Bass Module again and removed the I/O board (easy to access).
32. Cut the trace leading to the middle (3.3V) DE9 pin.
	- It leads to the same internal pin-header that the SmartSpeaker line goes to, so it seems to be intentional to have 3.3V there).
33. Soldered more breakout wires onto the 13-pin connected (V_UNREG, GND, left+, left-, right+, right-, SmartSpeaker, Mute) and carried to an external JR45 connector.
34. Just as a test, reconnected the Console to the Bass Module and probed the Mute signal; it hovers around 1.8V no matter if the Console is on or off.
	- It is either not implemented on this system (same as DSP_Shutdown, and software mute is used instead), or is an indication that there is more damage to circuitry.
	- For my replacement unit, I'm just going to ignore it as it seems to function fine while floating *(I still broke-out the wire to the external RJ45 jack just in case, though)*.

---

This concluded my original investigation and troubleshooting. Some details about my (Arduino-based) replacement Console can be found under the [ReplacementUnit](ReplacementUnit/README.md) directory.