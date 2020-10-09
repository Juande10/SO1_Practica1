import React, { Component } from 'react';
import logo from './logo.svg';
import './App.css';
import {Tab, Tabs} from 'react-bootstrap';

class App extends Component {
  render() {
    return (
      <div className="App">
        <div className="App-header">
          <img src={logo} className="App-logo" alt="logo" />
          <h2>Welcome to React</h2>
        </div>
        <div class="container-fluid m-4">
          <Tabs defaultActiveKey="profile" id="uncontrolled-tab-example" className="nav-fill">
            <Tab eventKey="home" title="Home">
              Hola bebe
            </Tab>
            <Tab eventKey="profile" title="Profile">
              Adios Bebe
            </Tab>
          </Tabs>
        </div>
      </div>
    );
  }
}

export default App;
