import React, { Component } from 'react';
import logo from './logo.svg';
import './App.css';
import {Tab, Tabs} from 'react-bootstrap';
import CPU from './components/cpu/cpu.js'

class App extends Component {
  render() {
    return (
      <div className="App">
        <div className="App-header">
          <img src={logo} className="App-logo" alt="logo" />
          <h2>Welcome to React</h2>
        </div>
        <div class="container-fluid m-4">
          <Tabs defaultActiveKey="servidorA" id="uncontrolled-tab-example" className="nav-fill">
            <Tab eventKey="servidorA" title="Home">
              <CPU URL={'http://35.232.49.94:5000'}></CPU>
            </Tab>
            <Tab eventKey="profile" title="Servidor B">
              Adios Bebe
            </Tab>
          </Tabs>
        </div>
      </div>
    );
  }
}

export default App;
