import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import Cover from './pages/Cover';
import Inventory from './pages/Inventory';
import MealIdeas from './pages/MealIdeas';
import RecipeDetail from './pages/RecipeDetail';
import ScanReceipt from './pages/ScanReceipt';
import './App.css';

function App() {
  return (
    <Router>
      <div className="app">
        <Routes>
          <Route path="/" element={<Cover />} />
          <Route path="/inventory" element={<Inventory />} />
          <Route path="/meal-ideas" element={<MealIdeas />} />
          <Route path="/recipe/:id" element={<RecipeDetail />} />
          <Route path="/scan-receipt" element={<ScanReceipt />} />
        </Routes>
      </div>
    </Router>
  );
}

export default App;
