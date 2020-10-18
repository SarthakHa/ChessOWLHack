import speech_recognition as sr
import pyttsx3
import sys,getopt
import time


if __name__ == "__main__":
    argv = sys.argv[1:]
    engine = pyttsx3.init()
    r = sr.Recognizer()

    opt, args = getopt.getopt(argv,"fi:o:")
    start = None
    end = None
    fail = False
    for o,a in opt:
        if o == "-f":
            fail = True
        if o == "-i":
            start = a
        if o == "-o":
            end = a
    print(start,end)
    
    if (start != None) and (end != None):
        engine.say("The move played by the opponent was " + start + " to " + end)
        engine.runAndWait()
    if fail:
        engine.say("Your last move was invalid, please repeat your move!")
        engine.runAndWait()
    else:
        engine.say("please say your move")
        engine.runAndWait()
    



    
    with sr.Microphone() as source:
        while (true):
            audio = r.listen(source)
            transcribed = r.recognize_google_cloud(audio)
            engine.say(transcribed)
            engine.runAndWait()
            engine.say("Was your move" + transcribed)
            engine.runAndWait()
            audio = r.listen(source)
            transcribed = r.recognize_google_cloud(audio)
            if transcribed == "yes":
                engine.say("Opponents turn now")
                print(transcribed)
                engine.runAndWait()
                break
            else:
                engine.say("State your move again")
                engine.runAndWait()


            
    