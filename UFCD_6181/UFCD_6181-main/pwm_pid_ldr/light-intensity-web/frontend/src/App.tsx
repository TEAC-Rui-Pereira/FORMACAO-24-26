import React from 'react';
import { BrowserRouter as Router, Route, Switch } from 'react-router-dom';
import Dashboard from './components/Dashboard';
import LightControl from './components/LightControl';
import './styles/main.css';

const App: React.FC = () => {
  return (
    <Router>
      <div className="App">
        <Switch>
          <Route path="/" exact component={Dashboard} />
          <Route path="/control" component={LightControl} />
        </Switch>
      </div>
    </Router>
  );
};

export default App;