import React, { Component } from 'react';
import './cpu.css';
import { Line } from 'react-chartjs-2';
import { Container, Row, Col } from 'react-bootstrap';
import axios from 'axios';


class CPU extends Component {
    constructor(props) {
        super(props);
        let data_percentage = {
          labels: [],
          datasets: [
            {
              label: '% de CPU utilizado',
              fill: false,
              lineTension: 0.1,
              backgroundColor: 'rgba(75,192,192,0.4)',
              borderColor: 'rgba(75,192,192,1)',
              borderCapStyle: 'butt',
              borderDash: [],
              borderDashOffset: 0.0,
              borderJoinStyle: 'miter',
              pointBorderColor: 'rgba(75,192,192,1)',
              pointBackgroundColor: 'rgba(75,192,192,1)',
              pointBorderWidth: 1,
              pointHoverRadius: 5,
              pointHoverBackgroundColor: 'rgba(75,192,192,1)',
              pointHoverBorderColor: 'rgba(220,220,220,1)',
              pointHoverBorderWidth: 2,
              pointRadius: 5,
              pointHitRadius: 10,
              data: []
            }
          ]
        };
        this.state = { labels: [], data: data_percentage.datasets[0].data, actual: 0, dataset: data_percentage};
    }
    
    componentDidMount() {
        
        this.interval = setInterval(() => {
          axios.get(this.props.URL + `/getCPU`)
            .then(res => {
              let labels1 = this.state.labels;
              let dt = new Date();
              labels1.push(dt.toLocaleTimeString());
              let data1 = this.state.data;
            
              data1.push(JSON.parse(res.data['cpu']).usado);
              if (labels1.length > 10) {
                labels1.shift();
                data1.shift();
              }
    
              this.setState({ data: data1 })
              //dataset
              let data_percentage = {
                labels: labels1,
                datasets: [
                  {
                    label: '% de CPU utilizado',
                    fill: false,
                    lineTension: 0.1,
                    backgroundColor: 'rgba(75,192,192,0.4)',
                    borderColor: 'rgba(75,192,192,1)',
                    borderCapStyle: 'butt',
                    borderDash: [],
                    borderDashOffset: 0.0,
                    borderJoinStyle: 'miter',
                    pointBorderColor: 'rgba(75,192,192,1)',
                    pointBackgroundColor: 'rgba(75,192,192,1)',
                    pointBorderWidth: 1,
                    pointHoverRadius: 5,
                    pointHoverBackgroundColor: 'rgba(75,192,192,1)',
                    pointHoverBorderColor: 'rgba(220,220,220,1)',
                    pointHoverBorderWidth: 2,
                    pointRadius: 5,
                    pointHitRadius: 10,
                    data: data1
                  }
                ]
              };
    
              this.setState({ actual: JSON.parse(res.data['cpu']).usado, labels: labels1, data: data1, dataset: data_percentage });
              let lineChart = this.reference.chartInstance
    
              lineChart.update();
    
    
            })
        }, 5000)
    }
        
    componentWillUnmount() {
        clearInterval(this.interval);
    }
    

    render() {
        return (
          <div>
            <Container fluid>
              <Row>
                <Col>
                  <h1> Porcentaje de CPU utilizado</h1>
                </Col>
              </Row>
              <Row>
                <Col>
                  <p > {this.state.actual}% en uso</p>
                </Col>
              </Row>
              <Row>
                <Col md={2}>
                </Col>
                <Col md={8}>
                  <Line data={this.state.dataset} ref={(reference) => this.reference = reference} />
                </Col>
              </Row>
    
            </Container>
    
          </div>
        );
    }
    
}

export default CPU;