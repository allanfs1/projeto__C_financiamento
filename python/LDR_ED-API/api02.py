
# -*- coding: utf-8 -*-
"""
Created on Thu Dez 15 19:21:15 2018

@author:????
servidor:Sistema que realiza coleta de dados remotamente
"""

from flask import Flask,request,jsonify,abort,render_template



app = Flask(__name__)#nome do app
app.config['DEBUG']=True

@app.route('/')
def index():
    return render_template('index.html')

@app.route("/dados/Ldr",methods=["GET"])
def luz_api():
    from ldrSolo import ldr
    if request.method == "GET":
         dados = ldr.run()
         return jsonify({"Luminancia":dados})

    else:
        return f'<html><body>{abort(404)}</body></html>'

    ldr.setDaemon(True)
    ldr.start()

if __name__ == "__main__":
    app.run(debug = True,use_reloader= True)
