# Multi-stage build for SustainHub WebApp

# Stage 1: Build the frontend
FROM node:20-alpine AS frontend-builder

WORKDIR /app/frontend

# Copy frontend package files
COPY frontend/package*.json ./

# Install frontend dependencies
RUN npm ci

# Copy frontend source code
COPY frontend/ ./

# Build the frontend for production
RUN npm run build

# Stage 2: Setup the backend and combine with frontend
FROM node:20-alpine AS production

WORKDIR /app

# Install production dependencies for backend
COPY backend/package*.json ./backend/
WORKDIR /app/backend
RUN npm ci --only=production

# Copy backend source code
COPY backend/ ./

# Copy built frontend from the first stage
COPY --from=frontend-builder /app/frontend/dist ../frontend/dist

# Create directory for database (will be mounted as volume in production)
RUN mkdir -p /app/data

# Expose the port the app runs on
EXPOSE 3001

# Set environment to production
ENV NODE_ENV=production
ENV PORT=3001

# Start the server
CMD ["node", "server.js"]
