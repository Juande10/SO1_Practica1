import React, { Component } from 'react';
import logo from './logo.svg';
import './App.css';
import {Tab, Tabs} from 'react-bootstrap';
import Monitor from './components/monitor/monitor.js';

class App extends Component {
  render() {
    return (
      <div className="App">
        <div className="App-header">
          <img src={logo} className="App-logo" alt="logo" />
          <h2>Practica 1 Sopes 1</h2>
        </div>
        <div className="container-fluid m-4">
          <Tabs defaultActiveKey="servidorA" id="uncontrolled-tab-example" className="nav-fill">
            <Tab eventKey="servidorA" title="Servidor A">
                <Monitor URL={'http://35.232.49.94:5000'}></Monitor>
            </Tab>
            <Tab eventKey="profile" title="Servidor B">
            < Monitor URL={'http://35.224.249.130:5000'}></Monitor>
            </Tab>
          </Tabs>
        </div>
      </div>
    );
  }
}

export default App;
